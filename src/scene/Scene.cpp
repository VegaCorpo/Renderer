#include "Scene.hpp"
#include <cstddef>

render::Scene::Scene() : _camera(nullptr), _celestialManager()
{}

void render::Scene::init(std::shared_ptr<ARenderer>& renderer, const common::SpecificDataRender& data)
{
    this->_renderer = renderer;

    this->_camera = std::make_unique<RenderCamera>();
    this->_camera->init();

    this->_celestialManager = std::make_unique<CelestialManager>(renderer);
    this->_celestialManager->initBodies(data);

    this->_camera->follow(std::size_t{3});
}

void render::Scene::handleAction(common::Action action)
{
    auto it = dispatchTable.find(action);

    if (it != dispatchTable.end()) {
        it->second(*this);
    }
}

void render::Scene::syncIn(const common::WorldState& world)
{
    if (this->_celestialManager) {
        this->_celestialManager->syncIn(world);
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
        Eigen::Vector3f pos = this->_celestialManager->getBodyPosition(this->_camera->getFollowedEntity());

        this->_camera->follow(pos);
    }
}

void render::Scene::render()
{
    this->_renderer->beginMode3D(this->_camera->getCameraView());

    this->_celestialManager->render3D(this->_camera->getCameraView());
    // DrawGrid(10, 100);

    this->_renderer->endMode3D();

    this->_celestialManager->render2D(this->_camera->getCameraView());
}
