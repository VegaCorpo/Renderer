#include "OrbitTrail.hpp"
#include <algorithm>
#include <iterator>

render::OrbitTrail::OrbitTrail(const float minDistance) :
    ADisplayOption(NAME, DESCRIPTION, Layer::SCENE_3D), _maxTrailPoints(MAX_TRAIL_POINTS), _minDistance(minDistance),
    _trails()
{
    this->_addParam<std::size_t>(PARAM_MAX_POINTS, PARAM_MAX_POINTS_DESCRIPTION, this->_maxTrailPoints);
    this->_addParam<float>(PARAM_MIN_DISTANCE, PARAM_MIN_DISTANCE_DESCRIPTION, this->_minDistance,
                           [](const float value) { return std::max(value, 0.f); });
}

void render::OrbitTrail::update(const std::size_t entity, const CelestialBody& body)
{
    // Trails[entity] is default-constructed on first access, and owns its
    // own point buffer directly — no separate copy of the trail data.
    auto& points = this->_trails[entity].points();
    const Eigen::Vector3f& position = body.getScenePosition();

    // The last point always sticks to the body; it only becomes a fixed
    // point once the body is far enough from the previous one
    if (points.size() >= MIN_TRAIL_POINTS) {
        const Eigen::Vector3f& lastFixedPoint = *std::next(points.rbegin());

        if ((position - lastFixedPoint).squaredNorm() < this->_minDistance * this->_minDistance) {
            points.back() = position;
            return;
        }
    }
    points.push_back(position);

    if (points.size() > this->_maxTrailPoints) {
        points.erase(points.begin(), points.end() - static_cast<std::ptrdiff_t>(this->_maxTrailPoints));
    }
}

void render::OrbitTrail::draw(const std::size_t entity, const CelestialBody& body,
                              const render::CameraView& /*cameraView*/, GLRenderer& renderer) const
{
    const auto it = this->_trails.find(entity);

    if (it == this->_trails.end()) {
        return;
    }
    it->second.setColor(body.getModelInfo()->dominantColor);
    it->second.draw(renderer, {});
}

void render::OrbitTrail::reset()
{
    this->_trails.clear();
}
