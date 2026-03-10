#include "Scene.hpp"
#include <components/mass.hpp>
#include <components/position.hpp>
#include <iostream>
#include <Mesh.hpp>
#include <vector>
#include "SolarSystemValues.hpp"

render::Scene::Scene() : _camera(nullptr)
{}

void render::Scene::init()
{
    this->_camera = std::make_unique<RenderCamera>();
    this->_camera->init();

    this->_sphereModel = std::make_unique<raylib::Model>(raylib::Mesh::Sphere(1.0f, 32, 32));
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

        Vector3 direction = {
        this->_moon.x - this->_earth.x,
        this->_moon.y - this->_earth.y,
        this->_moon.z - this->_earth.z
    };

    float length = sqrtf(direction.x * direction.x +
                         direction.y * direction.y +
                         direction.z * direction.z);

    if (length > 0.000001f) {
        direction.x /= length;
        direction.y /= length;
        direction.z /= length;
    }

    float d = DIST_EARTH_MOON_SCALED;

    this->_moon = {
        this->_earth.x + direction.x * d,
        this->_earth.y + direction.y * d,
        this->_earth.z + direction.z * d
    };
}

void render::Scene::render()
{
    int i = 0;
    std::vector<Color> colors = {GRAY, GREEN, ORANGE};

    // for (const auto& [entity, position] : _positions) {
    //     std::cout << "Drawing planet " << i++ << " at (" << position.x << ", " << position.y << ", " << position.z
    //               << ")" << std::endl;
    //     if (position.x == EARTH_POS * POSITION_SCALE) {
    //         _sphereModel->Draw(position, EARTH_RADIUS_RENDER, GREEN);
    //         continue;
    //     }
    //     if (position.x == MOON_POS * POSITION_SCALE) {
    //         _sphereModel->Draw(position, MOON_RADIUS_RENDER, GRAY);
    //         continue;
    //     }
    //     if (position.x == 0.f) {
    //         _sphereModel->Draw(position, SUN_RADIUS_RENDER, ORANGE);
    //         continue;
    //     }
    //     std::cerr << "Error: Position not handled\n" << std::endl;
    // }
    _sphereModel->Draw(this->_earth, EARTH_RADIUS_RENDER, GREEN);
    _sphereModel->Draw(this->_moon, MOON_RADIUS_RENDER, GRAY);
    _sphereModel->Draw(this->_sun, SUN_RADIUS_RENDER, ORANGE);
}
