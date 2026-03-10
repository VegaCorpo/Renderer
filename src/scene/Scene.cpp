#include "Scene.hpp"
#include <components/mass.hpp>
#include <components/position.hpp>
#include <Mesh.hpp>
#include "SolarSystemValues.hpp"

const std::unordered_map<common::Action, std::function<void(render::Scene&)>> render::Scene::dispatchTable = {
    {common::Action::MOVE_CAMERA_FORWARD, [](Scene& s) { s._camera->addMovement({0, 0, 1}); }},
    {common::Action::MOVE_CAMERA_BACKWARD, [](Scene& s) { s._camera->addMovement({0, 0, -1}); }},
    {common::Action::MOVE_CAMERA_UP, [](Scene& s) { s._camera->addMovement({0, 1, 0}); }},
    {common::Action::MOVE_CAMERA_DOWN, [](Scene& s) { s._camera->addMovement({0, -1, 0}); }},
    {common::Action::MOVE_CAMERA_LEFT, [](Scene& s) { s._camera->addMovement({-1, 0, 0}); }},
    {common::Action::MOVE_CAMERA_RIGHT, [](Scene& s) { s._camera->addMovement({1, 0, 0}); }},
    {common::Action::ROTATE_CAMERA_UP, [](Scene& s) { s._camera->addRotation({0, -1}); }},
    {common::Action::ROTATE_CAMERA_DOWN, [](Scene& s) { s._camera->addRotation({0, 1}); }},
    {common::Action::ROTATE_CAMERA_LEFT, [](Scene& s) { s._camera->addRotation({-1, 0}); }},
    {common::Action::ROTATE_CAMERA_RIGHT, [](Scene& s) { s._camera->addRotation({1, 0}); }},
};

render::Scene::Scene() : _camera(nullptr)
{}

void render::Scene::init()
{
    this->_camera = std::make_unique<RenderCamera>();
    this->_camera->init();

    this->_sphereModel = std::make_unique<raylib::Model>(raylib::Mesh::Sphere(1.0f, 32, 32));
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

    auto assignPosition = [&](entt::registry& registry, const entt::entity entity, Vector3& dest)
    {
        components::Position pos = registry.get<components::Position>(entity);
        dest = {pos.x * POSITION_SCALE, pos.y * POSITION_SCALE, pos.z * POSITION_SCALE};
    };

    registry.view<components::Mass>().each(
        [&](entt::entity entity, const components::Mass& mass)
        {
            if (mass.mantissa == EARTH_MANTISSA) {
                assignPosition(registry, entity, this->_earth);
            }
            if (mass.mantissa == MOON_MANTISSA) {
                assignPosition(registry, entity, this->_moon);
            }
            if (mass.mantissa == SUN_MANTISSA) {
                assignPosition(registry, entity, this->_sun);
            }
        });

    // Move the moon away from the earth because of the size
    Vector3 direction = {this->_moon.x - this->_earth.x, this->_moon.y - this->_earth.y,
                         this->_moon.z - this->_earth.z};

    float length = sqrtf(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z);

    if (length > 0.000001f) {
        direction.x /= length;
        direction.y /= length;
        direction.z /= length;
    }

    this->_moon = {this->_earth.x + direction.x * DIST_EARTH_MOON_SCALED,
                   this->_earth.y + direction.y * DIST_EARTH_MOON_SCALED,
                   this->_earth.z + direction.z * DIST_EARTH_MOON_SCALED};
}

void render::Scene::render()
{
    _sphereModel->Draw(this->_earth, EARTH_RADIUS_RENDER, GREEN);
    _sphereModel->Draw(this->_moon, MOON_RADIUS_RENDER, GRAY);
    _sphereModel->Draw(this->_sun, SUN_RADIUS_RENDER, ORANGE);
}
