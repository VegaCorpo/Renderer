#include "CelestialManager.hpp"
#include <components/mass.hpp>
#include <components/position.hpp>
#include <Mesh.hpp>
#include <iostream>
#include <raymath.h>
#include "CelestialBody.hpp"
#include "SolarSystemValues.hpp"

render::CelestialManager::CelestialManager() :
    _bodies(), _scaleMode(ScaleMode::VISUAL), _visualConfig(),
    _sphereModel(std::make_shared<raylib::Model>(raylib::Mesh::Sphere(1.0f, 32, 32)))
{}

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
    registry.view<components::Mass, components::Position>().each(
        [&](entt::entity entity, const components::Mass& mass, const components::Position& pos)
        {
            if (mass.mantissa == EARTH_MANTISSA) {
                this->addOrUpdateBody(entity, "earth", {pos.x, pos.y, pos.z}, EARTH_RADIUS, GREEN, this->_sphereModel);
            }
            if (mass.mantissa == MOON_MANTISSA) {
                this->addOrUpdateBody(entity, "moon", {pos.x, pos.y, pos.z}, MOON_RADIUS, GRAY, this->_sphereModel);
            }
            if (mass.mantissa == SUN_MANTISSA) {
                this->addOrUpdateBody(entity, "sun", {pos.x, pos.y, pos.z}, SUN_RADIUS, ORANGE, this->_sphereModel);
            }
        });

    if (this->_hasBodiesBeenModified()) {
        this->_scaleModeFunctions.at(this->_scaleMode)();
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

void render::CelestialManager::_realisticRescale()
{
    for (auto& [_, body] : _bodies) {
        body.computePositionAndScale(SCALE);
    }
}

void render::CelestialManager::_visualRescale()
{
    _computeVisualPositionScale();
    _computeVisualSizeScale();
}

void render::CelestialManager::_computeVisualSizeScale()
{
    // 1. Trouve le rayon max parmi tous les corps
    float maxRadius = 0.0f;
    for (const auto& [_, body] : _bodies) {
        maxRadius = std::max(maxRadius, body.getRealRadiusKm());
    }

    // 2. Applique l'algo choisi sur chaque corps
    for (auto& [_, body] : _bodies) {
        float visualScale = 0.0f;

        switch (_visualConfig.sizeAlgo) {
            case SizeAlgo::LOG:
            default:
                visualScale = _logSizeScale(body.getRealRadiusKm(), maxRadius);
                break;
        }

        body.setRenderScale(visualScale);
    }
}

void render::CelestialManager::_computeVisualPositionScale()
{
    // 1. Trouve la distance max (composante la plus éloignée de l'origine)
    float maxDistance = 0.0f;
    for (const auto& [_, body] : _bodies) {
        const Vector3& pos = body.getRealPositionKm();
        maxDistance = std::max(maxDistance, std::abs(pos.x));
        maxDistance = std::max(maxDistance, std::abs(pos.y));
        maxDistance = std::max(maxDistance, std::abs(pos.z));
    }

    // 2. Applique l'algo choisi sur chaque corps
    for (auto& [_, body] : _bodies) {
        Vector3 visualPos = {};

        switch (_visualConfig.positionAlgo) {
            case PositionAlgo::LOG:
            default:
                visualPos = _logPositionScale(body.getRealPositionKm(), maxDistance);
                break;
        }

        body.setScenePosition(visualPos);
    }
}

float render::CelestialManager::_logSizeScale(float realRadius, float maxRadius) const
{
    if (maxRadius <= 0.0f)
        return _visualConfig.minVisualRadius;

    const float k = _visualConfig.logBoostFactor;
    const float normalized = realRadius / maxRadius;

    // Double log : compresse mieux les grandes différences d'échelle
    const float logScale = std::log(1.0f + std::log(1.0f + normalized * k)) / std::log(1.0f + std::log(1.0f + k));

    const float visual = logScale * _visualConfig.maxVisualRadius;
    return std::max(visual, _visualConfig.minVisualRadius);
}

Vector3 render::CelestialManager::_logPositionScale(const Vector3& realPos, float maxDistance) const
{
    if (maxDistance <= 0.0f)
        return {0.0f, 0.0f, 0.0f};

    const float magnitude = Vector3Length(realPos);
    if (magnitude <= 0.0f)
        return {0.0f, 0.0f, 0.0f};

    const float k = _visualConfig.logBoostFactor;
    const float normalized = magnitude / maxDistance; // 0..1
    const float logScale = std::log(1.0f + normalized * k) / std::log(1.0f + k); // 0..1
    const float visualMag = logScale * _visualConfig.maxVisualDistance;

    // Conserve la direction, applique la magnitude log
    return Vector3Scale(Vector3Normalize(realPos), visualMag);
}
