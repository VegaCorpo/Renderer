#include "Scene.hpp"

render::Scene::Scene() : _camera(nullptr), _celestialManager()
{}

void render::Scene::init()
{
    this->_camera = std::make_unique<RenderCamera>();
    this->_camera->init();

    this->_celestialManager = std::make_unique<CelestialManager>();
}

void render::Scene::handleAction(common::Action action)
{
    auto it = dispatchTable.find(action);

    if (it != dispatchTable.end()) {
        it->second(*this);
    }
}

void render::Scene::update(entt::registry& registry)
{
    if (this->_camera)
        this->_camera->update();

    if (this->_celestialManager)
        this->_celestialManager->update(registry);
}

void render::Scene::render()
{
    BeginMode3D(this->_camera->getCamera());

    this->_celestialManager->render();

    EndMode3D();
}
