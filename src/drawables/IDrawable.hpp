#pragma once
#include <Eigen/Dense>

namespace render {
    class GLRenderer;

    // Minimal data needed to place a drawable in the scene at draw time.
    struct Transform {
            Eigen::Vector3f position{};
            float scale = 1.0f;
    };

    // Base class for anything that can put pixels on screen. Scene-side code
    // (CelestialBody, features) only ever talks to this interface — it never
    // includes GLRenderer.hpp or calls a GL function directly.
    class IDrawable {
        public:
            virtual ~IDrawable() = default;
            virtual void draw(GLRenderer& gl, const Transform& transform) const = 0;
    };
} // namespace render
