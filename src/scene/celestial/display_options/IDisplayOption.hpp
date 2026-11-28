#pragma once

#include <cstddef>
#include <types/DisplayOption.hpp>
#include <vector>
#include "CelestialBody.hpp"
#include "RenderTypes.hpp"

namespace render {
    class GLRenderer;

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

            [[nodiscard]] virtual std::vector<common::DisplayOptionParam> params() const = 0;
            virtual void setParams(const std::vector<common::DisplayOptionParam>& params) = 0;

            [[nodiscard]] virtual common::DisplayOption toDisplayOption(common::DisplayOptionId id) const = 0;
    };
} // namespace render
