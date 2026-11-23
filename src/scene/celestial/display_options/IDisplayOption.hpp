#pragma once

#include <cstddef>
#include <types/DisplayOption.hpp>
#include <vector>
#include "CelestialBody.hpp"
#include "RenderTypes.hpp"

namespace render {
    class GLRenderer;

    // A display option only receives the renderer as a draw()-time parameter — it
    // never stores it, so it stays decoupled from the graphics backend
    class IDisplayOption {
        public:
            virtual ~IDisplayOption() = default;

            virtual void update(std::size_t entity, const CelestialBody& body) = 0;
            virtual void draw(std::size_t entity, const CelestialBody& body, const render::CameraView& cameraView,
                              GLRenderer& renderer) const = 0;

            virtual void reset() = 0;

            [[nodiscard]] virtual bool is2D() const = 0;

            // Tunable parameters exposed to the UI, none by default
            [[nodiscard]] virtual std::vector<common::DisplayOptionParam> params() const { return {}; }
    };
} // namespace render
