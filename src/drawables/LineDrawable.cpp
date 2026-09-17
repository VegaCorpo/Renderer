#include "LineDrawable.hpp"
#include "GLRenderer.hpp"

void render::LineDrawable::draw(GLRenderer& renderer, const Transform& transform) const
{
    if (this->_points.size() < 2)
        return;

    for (std::size_t i = 0; i + 1 < this->_points.size(); ++i) {
        renderer.drawLine3D(this->_points[i] + transform.position, this->_points[i + 1] + transform.position,
                            this->_color);
    }
}
