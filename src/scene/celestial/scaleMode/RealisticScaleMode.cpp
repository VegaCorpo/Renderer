#include "RealisticScaleMode.hpp"
#include <cmath>

render::RealisticScaleMode::RealisticScaleMode() : _scaleComputed(false), _distanceScale(1.f)
{}

void render::RealisticScaleMode::rescale(std::unordered_map<entt::entity, CelestialBody>& bodies)
{
    if (!_scaleComputed) {
        float maxDistanceKm = _computeMaxDistance(bodies);

        if (maxDistanceKm <= 0.0001f)
            _distanceScale = 1.f;
        else
            _distanceScale = MAX_SCENE_DISTANCE / maxDistanceKm;

        _scaleComputed = true;
    }

    _applyScale(bodies);
}

float render::RealisticScaleMode::_computeMaxDistance(const std::unordered_map<entt::entity, CelestialBody>& bodies)
{
    float maxDist = 0.f;

    for (const auto& [entity, body] : bodies) {
        Vector3 pos = body.getRealPositionKm();
        float dist = std::sqrt(pos.x * pos.x + pos.y * pos.y + pos.z * pos.z);
        if (dist > maxDist)
            maxDist = dist;
    }
    return maxDist;
}

void render::RealisticScaleMode::_applyScale(std::unordered_map<entt::entity, CelestialBody>& bodies) const
{
    for (auto& [entity, body] : bodies) {
        body.computePositionAndScale(this->_distanceScale);
    }
}
