#include "LineDrawable.hpp"
#include "GLRenderer.hpp"

void render::LineDrawable::draw(GLRenderer& renderer, const Transform& transform) const
{
    if (this->_points.size() < 2)
        return;

    std::vector<Eigen::Vector3f> worldPoints;
    worldPoints.reserve(this->_points.size());
    for (const auto& point : this->_points)
        worldPoints.push_back(point + transform.position);

    renderer.drawLineStrip(worldPoints, this->_color);
}
