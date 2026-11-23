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

            [[nodiscard]] virtual bool isEnabled() const = 0;
            virtual void setEnabled(bool enabled) = 0;

            // Tunable parameters exposed to the UI
            [[nodiscard]] virtual std::vector<common::DisplayOptionParam> params() const = 0;
            // Apply the parameters sent back by the UI, unknown names or wrong types are ignored
            virtual void setParams(const std::vector<common::DisplayOptionParam>& params) = 0;

            // Everything the UI needs to know about this option
            [[nodiscard]] virtual common::DisplayOption toDisplayOption(common::DisplayOptionId id) const = 0;
    };
} // namespace render
