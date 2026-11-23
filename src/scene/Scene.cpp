#include "Scene.hpp"

render::Scene::Scene() : _camera(nullptr), _celestialManager()
{}

void render::Scene::init(std::shared_ptr<GLRenderer>& renderer, const common::SpecificDataRender& data)
{
    this->_renderer = renderer;

    this->_camera = std::make_unique<RenderCamera>();
    this->_camera->init();

    this->_celestialManager = std::make_unique<CelestialManager>(renderer);
    this->_celestialManager->initBodies(data);
}

void render::Scene::handleAction(const common::InputAction& action)
{
    auto it = dispatchTable.find(action.action);

    if (it != dispatchTable.end()) {
        it->second(*this, action);
    }
}

void render::Scene::syncIn(const common::WorldState& world)
{
    if (this->_celestialManager) {
        this->_celestialManager->syncIn(world);
    }
}

void render::Scene::syncUIData(const common::SpecificDataUI& data)
{
    if (this->_camera) {
        this->_camera->follow(data.camFocusEnt);
    }
}

std::vector<common::DisplayOption> render::Scene::getDisplayOptions() const
{
    if (!this->_celestialManager) {
        return {};
    }
    return this->_celestialManager->getDisplayOptions();
}

void render::Scene::updateDisplayOptions(const std::vector<common::DisplayOption>& options)
{
    if (!this->_celestialManager) {
        return;
    }
    for (const auto& option : options) {
        this->_celestialManager->updateDisplayOption(option);
    }
}

void render::Scene::update()
{
    if (!this->_camera || !this->_celestialManager) {
        throw std::runtime_error("Scene not initialized");
    }

    this->_celestialManager->update();

    this->_camera->update();

    std::optional<BoundingSphere> followedBounds;

    if (this->_camera->isFollowing()) {
        followedBounds = this->_celestialManager->getBodyBounds(this->_camera->getFollowedEntity());

        if (!followedBounds) {
            this->_camera->follow();
        }
    }

    if (this->_camera->isZooming()) {
        const auto bounds = this->_camera->isFollowing() ? followedBounds : this->_celestialManager->getSceneBounds();

        if (bounds) {
            this->_camera->updateZoom(*bounds);
        } else {
            this->_camera->cancelZoom();
        }
    } else if (followedBounds) {
        this->_camera->updateFollow(followedBounds->center);
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
