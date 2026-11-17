#include "CelestialManager.hpp"
#include <algorithm>
#include <components/name.hpp>
#include <limits>
#include <utils/assets.hpp>
#include "OrbitTrail.hpp"

render::CelestialManager::CelestialManager(std::shared_ptr<GLRenderer>& renderer) :
    _renderer(renderer), _resourceManager(nullptr), _bodies(), _scaleMode(ScaleMode::REALISTIC),
    _scaleStrategy(nullptr), _visualConfig(), _features(), _enabledFeatures()
{
    this->_resourceManager = std::make_unique<ResourceManager>(this->_renderer);

    this->_updateScaleStrategy();

    this->_features[static_cast<std::size_t>(Feature::TRAILS)] = std::make_unique<OrbitTrail>();
    this->_enabledFeatures.set();
}

template <typename Func>
void render::CelestialManager::_forEachEnabledFeature(Func&& func) const
{
    for (std::size_t i = 0; i < FEATURE_COUNT; i += 1) {
        if (this->_enabledFeatures.test(i) && this->_features[i]) {
            func(*this->_features[i]);
        }
    }
}

void render::CelestialManager::toggleFeature(Feature feature)
{
    const auto index = static_cast<std::size_t>(feature);

    this->_enabledFeatures.flip(index);

    // Restart from scratch so a trail doesn't join its old and new points
    if (this->_enabledFeatures.test(index) && this->_features[index]) {
        this->_features[index]->reset();
    }
}

void render::CelestialManager::changeScaleMode()
{
    this->_scaleMode = static_cast<ScaleMode>((static_cast<int>(this->_scaleMode) + 1) %
                                              static_cast<int>(ScaleMode::SCALE_MODE_NUMBER));

    this->_updateScaleStrategy();

    if (!this->_bodies.empty()) {
        this->_bodies.begin()->second.modified();
    }
}

void render::CelestialManager::initBodies(const common::SpecificDataRender& data)
{
    const std::size_t count =
        std::min({data.entitiesId.size(), data.names.size(), data.radius.size(), data.textures.size()});

    for (std::size_t i = 0; i < count; i += 1) {
        auto& body = this->_bodies[data.entitiesId[i]];

        body.setName(data.names[i].value);
        body.setRealRadiusKm(data.radius[i].value);
        body.setModelInfo(this->_resourceManager->getOrCreateModelInfo(data.textures[i].path));

        if (!body.getModelInfo()) {
            body.setModelInfo(this->_resourceManager->getOrCreateModelInfo(common::DEFAULT_TEXTURE_PATH));
        }

        this->_batchesByTexture[body.getModelInfo()->texture].push_back(data.entitiesId[i]);

        if (!this->_lightSource || body.getRealRadiusKm() > this->_bodies.at(*this->_lightSource).getRealRadiusKm()) {
            this->_lightSource = data.entitiesId[i];
        }

        body.init();
    }
}

void render::CelestialManager::syncIn(const common::WorldState& world)
{
    const std::size_t count = std::min(world.entitiesId.size(), world.positions.size());

    for (std::size_t i = 0; i < count; i += 1) {
        auto it = this->_bodies.find(world.entitiesId[i]);

        if (it == this->_bodies.end()) {
            continue;
        }

        const auto& pos = world.positions[i];
        it->second.setRealPositionKm(
            _physicsToRenderFrame() *
            Eigen::Vector3f(static_cast<float>(pos.x), static_cast<float>(pos.y), static_cast<float>(pos.z)));

        if (i < world.orientations.size()) {
            const auto& rot = world.orientations[i];
            it->second.setOrientation((_physicsToRenderFrame() *
                                       Eigen::Quaternionf(static_cast<float>(rot.scalar), static_cast<float>(rot.x),
                                                          static_cast<float>(rot.y), static_cast<float>(rot.z)))
                                          .normalized());
        }
    }
}

void render::CelestialManager::update()
{
    if (this->_scaleStrategy && this->_hasBodiesBeenModified()) {
        this->_scaleStrategy->rescale(this->_bodies);
    }

    for (auto& [entity, body] : this->_bodies) {
        this->_forEachEnabledFeature([&](IRenderFeature& feature) { feature.update(entity, body); });
    }
}

std::optional<render::BoundingSphere> render::CelestialManager::getBodyBounds(std::size_t entity) const
{
    auto it = this->_bodies.find(entity);

    if (it == this->_bodies.end()) {
        return std::nullopt;
    }
    return BoundingSphere{.center = it->second.getScenePosition(), .radius = it->second.getRenderScale()};
}

std::optional<render::BoundingSphere> render::CelestialManager::getSceneBounds() const
{
    if (this->_bodies.empty()) {
        return std::nullopt;
    }

    Eigen::Vector3f min = Eigen::Vector3f::Constant(std::numeric_limits<float>::max());
    Eigen::Vector3f max = Eigen::Vector3f::Constant(std::numeric_limits<float>::lowest());

    for (const auto& [entity, body] : this->_bodies) {
        const Eigen::Vector3f extent = Eigen::Vector3f::Constant(body.getRenderScale());

        min = min.cwiseMin(body.getScenePosition() - extent);
        max = max.cwiseMax(body.getScenePosition() + extent);
    }

    BoundingSphere bounds{.center = (min + max) * 0.5f, .radius = 0.0f};

    for (const auto& [entity, body] : this->_bodies) {
        bounds.radius =
            std::max(bounds.radius, (body.getScenePosition() - bounds.center).norm() + body.getRenderScale());
    }
    return bounds;
}

void render::CelestialManager::render3D(const render::CameraView& cameraView) const
{
    MeshHandle baseMesh = this->_resourceManager->getBaseMesh();
    const CelestialBody* lightBody = this->_lightSource ? &this->_bodies.at(*this->_lightSource) : nullptr;

    if (lightBody) {
        this->_renderer->setLightPosition(lightBody->getScenePosition());
    }

    // Use Batched map to draw bodies efficiently by textures
    for (const auto& [texture, entities] : this->_batchesByTexture) {
        std::vector<Eigen::Matrix4f> models;
        models.reserve(entities.size());

        for (std::size_t entity : entities) {
            const CelestialBody& body = this->_bodies.at(entity);

            _drawBodyFeatures(entity, body, cameraView);

            if (&body != lightBody) {
                models.push_back(_buildModelMatrix(body));
            }
        }

        this->_renderer->drawMeshInstanced(baseMesh, texture, models);
    }

    // The light source can't light itself: draw it on its own, unlit
    if (lightBody) {
        this->_renderer->drawMeshInstanced(baseMesh, lightBody->getModelInfo()->texture,
                                           {_buildModelMatrix(*lightBody)}, false);
    }
}

void render::CelestialManager::render2D(const render::CameraView& cameraView) const
{
    for (auto& [entity, body] : this->_bodies) {
        this->_forEachEnabledFeature(
            [&](IRenderFeature& feature)
            {
                if (feature.is2D()) {
                    feature.draw(entity, body, cameraView, *this->_renderer);
                }
            });
    }
}

void render::CelestialManager::_updateScaleStrategy()
{
    this->_scaleStrategy = this->_scaleModes.at(this->_scaleMode)();
    this->_renderer->setMinPixelRadius(this->_scaleStrategy->getMinPixelRadius());

    for (auto& feature : this->_features) {
        if (feature) {
            feature->reset();
        }
    }
}

bool render::CelestialManager::_hasBodiesBeenModified()
{
    bool isModified = false;

    for (auto& [_, body] : this->_bodies) {
        if (body.hasBeenModified()) {
            isModified = true;
            return isModified;
        }
    }

    return isModified;
}

void render::CelestialManager::_drawBodyFeatures(std::size_t entity, const CelestialBody& body,
                                                 const CameraView& cameraView) const
{
    this->_forEachEnabledFeature(
        [&](IRenderFeature& feature)
        {
            if (!feature.is2D()) {
                feature.draw(entity, body, cameraView, *this->_renderer);
            }
        });
}

const Eigen::Quaternionf& render::CelestialManager::_meshToBodyFrame()
{
    // The sphere mesh has its poles on Y, while physics spins bodies around their local Z axis
    // (common::rotation::BODY_SPIN_AXIS): rotate the mesh once so its poles line up with Z.
    static const Eigen::Quaternionf meshToBodyFrame(
        Eigen::AngleAxisf(static_cast<float>(EIGEN_PI) / 2.0f, Eigen::Vector3f::UnitX()));
    return meshToBodyFrame;
}

const Eigen::Quaternionf& render::CelestialManager::_physicsToRenderFrame()
{
    // Physics is Z-up (orbital plane XY) while the renderer is Y-up: rotate -90° around X,
    // (x, y, z) -> (x, z, -y). A rotation, not a Y/Z swap, so the scene isn't mirrored.
    static const Eigen::Quaternionf physicsToRenderFrame(
        Eigen::AngleAxisf(-static_cast<float>(EIGEN_PI) / 2.0f, Eigen::Vector3f::UnitX()));
    return physicsToRenderFrame;
}

Eigen::Matrix4f render::CelestialManager::_buildModelMatrix(const CelestialBody& body)
{
    Eigen::Matrix4f model = Eigen::Matrix4f::Identity();
    model.block<3, 1>(0, 3) = body.getScenePosition();
    model.block<3, 3>(0, 0) = (body.getOrientation() * _meshToBodyFrame()).toRotationMatrix() * body.getRenderScale();
    return model;
}
