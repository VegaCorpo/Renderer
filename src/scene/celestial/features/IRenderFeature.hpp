#pragma once

#include <cstddef>
#include "CelestialBody.hpp"
#include "RenderTypes.hpp"

namespace render {
    class IRenderFeature {
        public:
            virtual ~IRenderFeature() = default;

            virtual void update(std::size_t entity, const CelestialBody& body) = 0;
            virtual void draw(std::size_t entity, const CelestialBody& body, const render::CameraView& cameraView) const = 0;

            virtual void reset() = 0;

            [[nodiscard]] virtual bool is2D() const = 0;
    };
} // namespace render
