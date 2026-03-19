#include "Scene.hpp"
#include <entt/entity/fwd.hpp>

render::Scene::Scene() : _camera(nullptr), _celestialManager()
{}

void render::Scene::init()
{
    this->_camera = std::make_unique<RenderCamera>();
    this->_camera->init();

    this->_celestialManager = std::make_unique<CelestialManager>();

    this->_camera->follow(static_cast<entt::entity>(0));
}

void render::Scene::handleAction(common::Action action)
{
    auto it = dispatchTable.find(action);

    if (it != dispatchTable.end()) {
        it->second(*this);
    }
}

void render::Scene::syncIn(entt::registry& registry)
{
    if (this->_celestialManager) {
        this->_celestialManager->syncIn(registry);
    }
}

void render::Scene::update()
{
    if (!this->_camera || !this->_celestialManager) {
        throw std::runtime_error("Scene not initialized");
    }

    this->_celestialManager->update();

    this->_camera->update();

    if (this->_camera->isFollowing()) {
        Vector3 pos = this->_celestialManager->getBodyPosition(this->_camera->getFollowedEntity());

        this->_camera->follow(pos);
    }
}

void render::Scene::render()
{
    BeginMode3D(this->_camera->getCamera());

    this->_celestialManager->render3D(this->_camera->getCamera());
    DrawGrid(10, 100);

    EndMode3D();

    this->_celestialManager->render2D(this->_camera->getCamera());
}
