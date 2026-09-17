#pragma once

#include <vector>
#include "IDrawable.hpp"
#include "RenderTypes.hpp"

namespace render {
    // Draws a poly-line through a set of points, e.g. an orbit trail.
    // Owns its point buffer directly so the feature that fills it (OrbitTrail)
    // doesn't need to keep a separate copy of the same data.
    class LineDrawable : public IDrawable {
        public:
            LineDrawable() = default;
            explicit LineDrawable(Color color) : _color(color) {}

            [[nodiscard]] std::vector<Eigen::Vector3f>& points() { return _points; }
            void setColor(Color color) { _color = color; }

            void draw(GLRenderer& renderer, const Transform& transform) const override;

        private:
            std::vector<Eigen::Vector3f> _points;
            Color _color = Color::White();
    };
} // namespace render
