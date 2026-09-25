#include "RealisticScaleMode.hpp"
#include <cmath>

render::RealisticScaleMode::RealisticScaleMode() : _scaleComputed(false), _distanceScale(1.f)
{}

void render::RealisticScaleMode::rescale(std::unordered_map<std::size_t, CelestialBody>& bodies)
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

float render::RealisticScaleMode::_computeMaxDistance(const std::unordered_map<std::size_t, CelestialBody>& bodies)
{
    float maxSqDist = 0.f;

    for (const auto& [entity, body] : bodies) {
        float sqDist = body.getRealPositionKm().squaredNorm();
        if (sqDist > maxSqDist)
            maxSqDist = sqDist;
    }

    return std::sqrt(maxSqDist);
}

void render::RealisticScaleMode::_applyScale(std::unordered_map<std::size_t, CelestialBody>& bodies) const
{
    for (auto& [entity, body] : bodies) {
        body.computePositionAndScale(this->_distanceScale);
    }
}
