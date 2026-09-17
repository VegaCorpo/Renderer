#pragma once

#include <entt/entt.hpp>
#include "CelestialBody.hpp"
#include "RenderTypes.hpp"

namespace render {
    class GLRenderer;

    // A feature only receives the renderer as a draw()-time parameter — it
    // never stores it, so it stays decoupled from the graphics backend
    class IRenderFeature {
        public:
            virtual ~IRenderFeature() = default;

            virtual void update(entt::entity entity, const CelestialBody& body) = 0;
            virtual void draw(entt::entity entity, const CelestialBody& body, const render::CameraView& cameraView,
                              GLRenderer& renderer) const = 0;

            virtual void reset() = 0;

            [[nodiscard]] virtual bool is2D() const = 0;
    };
} // namespace render
