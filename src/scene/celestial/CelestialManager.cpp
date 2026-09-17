#include "CelestialManager.hpp"
#include <components/name.hpp>
#include <utils/assets.hpp>
#include "MeshDrawable.hpp"
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

void render::CelestialManager::_addOrUpdateBody(entt::entity entity, entt::registry& registry,
                                                common::components::Position pos, common::components::Radius radius)
{
    auto& body = this->_bodies[entity];

    body.setRealPositionKm(
        Eigen::Vector3f(static_cast<float>(pos.x), static_cast<float>(pos.y), static_cast<float>(pos.z)));
    body.setRealRadiusKm(radius.value);

    if (body.hasBeenInitialized()) {
        return;
    }

    if (auto nameCpn = registry.try_get<common::components::Name>(entity)) {
        body.setName(nameCpn->value);
    }

    if (auto texture = registry.try_get<common::components::Texture>(entity)) {
        auto model = this->_resourceManager->getOrCreateModelInfo(texture->path);
        body.setModelInfo(model);
    }

    if (!body.getModelInfo()) {
        body.setModelInfo(this->_resourceManager->getOrCreateModelInfo(common::DEFAULT_TEXTURE_PATH));
    }

    // The only place that knows both the body's texture and the shared base
    // mesh — CelestialBody itself never touches either handle directly.
    body.setDrawable(
        std::make_shared<MeshDrawable>(this->_resourceManager->getBaseMesh(), body.getModelInfo()->texture));

    body.init();
}

void render::CelestialManager::syncIn(entt::registry& registry)
{
    registry.view<common::components::Position, common::components::Radius>().each(
        [&](entt::entity entity, common::components::Position pos, common::components::Radius radius)
        { _addOrUpdateBody(entity, registry, pos, radius); });
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

Eigen::Vector3f render::CelestialManager::getBodyPosition(entt::entity entity) const
{
    auto it = this->_bodies.find(entity);

    if (it == this->_bodies.end()) {
        return Eigen::Vector3f{0, 0, 0};
    }
    return it->second.getScenePosition();
}

void render::CelestialManager::render3D(const render::CameraView& cameraView) const
{
    for (auto& [entity, body] : this->_bodies) {
        for (auto& feature : this->_features) {
            if (!feature->is2D()) {
                feature->draw(entity, body, cameraView, *this->_renderer);
            }
        }

        body.draw(*this->_renderer);
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
