#include "CelestialManager.hpp"
#include <components/name.hpp>
#include <components/textureId.hpp>
#include <memory>
#include <raymath.h>
#include <utils/assets.hpp>
#include "CelestialBody.hpp"

render::CelestialManager::CelestialManager() :
    _resourceManager(nullptr), _bodies(), _scaleMode(ScaleMode::VISUAL), _visualConfig(), _scaleStrategy(nullptr)
{
    this->_resourceManager = std::make_unique<ResourceManager>();

    this->_updateScaleStrategy();
}

void render::CelestialManager::_addOrUpdateBody(entt::entity entity, entt::registry& registry,
                                                common::components::Position pos, common::components::Radius radius)
{
    auto& body = this->_bodies[entity];

    body.setRealPositionKm(Vector3(static_cast<float>(pos.x), static_cast<float>(pos.y), static_cast<float>(pos.z)));
    body.setRealRadiusKm(radius.value);

    if (body.hasBeenInitialized()) {
        return;
    }

    if (auto nameCpn = registry.try_get<common::components::Name>(entity)) {
        body.setName(nameCpn->value);
    }

    if (auto texture = registry.try_get<common::components::Texture>(entity)) {
        auto model = this->_resourceManager->getOrCreateModel(texture->path);
        body.setModel(model);
    }

    if (!body.getModel()) {
        body.setModel(this->_resourceManager->getOrCreateModel(common::DEFAULT_TEXTURE_PATH));
    }

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
}

void render::CelestialManager::render() const
{
    for (auto& [_, body] : this->_bodies) {
        body.render();
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
