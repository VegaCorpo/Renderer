#include "CelestialManager.hpp"
#include <components/mass.hpp>
#include <components/position.hpp>
#include <Mesh.hpp>
#include <raylib.h>
#include <raymath.h>
#include "CelestialBody.hpp"
#include "SolarSystemValues.hpp"

render::CelestialManager::CelestialManager() :
    _bodies(), _scaleMode(ScaleMode::VISUAL), _visualConfig(), _scaleStrategy(nullptr), _sphereModel(),
    _defaultTexture()
{
    Mesh mesh = raylib::Mesh::Sphere(1, 32, 32);
    this->_sphereModel = std::make_shared<raylib::Model>(mesh);
    this->_defaultTexture = LoadTexture("Renderer/assets/textures/2k_earth_texture.jpg");

    this->_sphereModel->materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = this->_defaultTexture;

    this->_updateScaleStrategy();
}

void render::CelestialManager::addOrUpdateBody(entt::entity entity, const std::string& name,
                                               const Vector3& realPosition, float realRadiusKm, Color color,
                                               std::shared_ptr<raylib::Model>& model)
{
    CelestialBody body = {};

    if (this->_bodies.find(entity) != this->_bodies.end()) {
        body = this->_bodies.at(entity);
    }

    body.setName(name);
    body.setRealPositionKm(realPosition);
    body.setRealRadiusKm(realRadiusKm);
    body.setModel(model);
    body.setColor(color);

    this->_bodies[entity] = body;
}

void render::CelestialManager::update(entt::registry& registry)
{
    registry
        .view<common::components::Mass, common::components::Position /*, component::Radius component::Color, component::texture ??*/>()
        .each(
            [&](entt::entity entity, const common::components::Mass& mass, const common::components::Position& pos)
            {
                if (mass.mantissa == EARTH_MANTISSA) {
                    this->addOrUpdateBody(entity, "Earth", {static_cast<float>(pos.x), static_cast<float>(pos.y), static_cast<float>(pos.z)}, EARTH_RADIUS, GREEN,
                                          this->_sphereModel);
                }
                if (mass.mantissa == MOON_MANTISSA) {
                    this->addOrUpdateBody(entity, "Moon", {static_cast<float>(pos.x), static_cast<float>(pos.y), static_cast<float>(pos.z)}, MOON_RADIUS, GRAY, this->_sphereModel);
                }
                if (mass.mantissa == SUN_MANTISSA) {
                    this->addOrUpdateBody(entity, "Sun", {static_cast<float>(pos.x), static_cast<float>(pos.y), static_cast<float>(pos.z)}, SUN_RADIUS, WHITE, this->_sphereModel);
                }
            });

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
        }
    }

    return isModified;
}
