#include "CelestialManager.hpp"
#include <algorithm>
#include <components/name.hpp>
#include <utils/assets.hpp>
#include "OrbitTrail.hpp"

render::CelestialManager::CelestialManager(std::shared_ptr<GLRenderer>& renderer) :
    _renderer(renderer), _resourceManager(nullptr), _bodies(), _scaleMode(ScaleMode::REALISTIC),
    _scaleStrategy(nullptr), _visualConfig(), _features()
{
    this->_resourceManager = std::make_unique<ResourceManager>(this->_renderer);

    this->_updateScaleStrategy();

    this->_features.push_back(std::make_unique<OrbitTrail>());
    // this->_features.push_back(std::make_unique<CelestialIcons>());
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
            Eigen::Vector3f(static_cast<float>(pos.x), static_cast<float>(pos.y), static_cast<float>(pos.z)));
    }
}

void render::CelestialManager::update()
{
    if (this->_scaleStrategy && this->_hasBodiesBeenModified()) {
        this->_scaleStrategy->rescale(this->_bodies);
    }

    for (auto& [entity, body] : this->_bodies) {
        for (auto& feature : this->_features) {
            feature->update(entity, body);
        }
    }
}

Eigen::Vector3f render::CelestialManager::getBodyPosition(std::size_t entity) const
{
    auto it = this->_bodies.find(entity);

    if (it == this->_bodies.end()) {
        return Eigen::Vector3f{0, 0, 0};
    }
    return it->second.getScenePosition();
}

void render::CelestialManager::render3D(const render::CameraView& cameraView) const
{
    MeshHandle baseMesh = this->_resourceManager->getBaseMesh();

    // Use Batched map to draw bodies efficiently by textures
    for (const auto& [texture, entities] : this->_batchesByTexture) {
        std::vector<Eigen::Matrix4f> models;
        models.reserve(entities.size());

        for (std::size_t entity : entities) {
            const CelestialBody& body = this->_bodies.at(entity);

            models.push_back(_buildModelMatrix(body));
            _drawBodyFeatures(entity, body, cameraView);
        }

        this->_renderer->drawMeshInstanced(baseMesh, texture, models);
    }
}

void render::CelestialManager::render2D(const render::CameraView& cameraView) const
{
    for (auto& [entity, body] : this->_bodies) {
        for (auto& feature : this->_features) {
            if (feature->is2D()) {
                feature->draw(entity, body, cameraView, *this->_renderer);
            }
        }
    }
}

void render::CelestialManager::_updateScaleStrategy()
{
    this->_scaleStrategy = this->_scaleModes.at(this->_scaleMode)();

    for (auto& feature : this->_features) {
        feature->reset();
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
    for (auto& feature : this->_features) {
        if (!feature->is2D()) {
            feature->draw(entity, body, cameraView, *this->_renderer);
        }
    }
}

Eigen::Matrix4f render::CelestialManager::_buildModelMatrix(const CelestialBody& body)
{
    Eigen::Matrix4f model = Eigen::Matrix4f::Identity();
    model.block<3, 1>(0, 3) = body.getScenePosition();
    model.block<3, 3>(0, 0) *= body.getRenderScale();
    return model;
}
