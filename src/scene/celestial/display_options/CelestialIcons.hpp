#pragma once

#include "IDisplayOption.hpp"

namespace render {
    class CelestialIcons : public IDisplayOption {
        public:
            void update(std::size_t entity, const CelestialBody& body) override {
            } //! to implement to save cameraview and if changed recompute icon

            void draw(std::size_t entity, const CelestialBody& body, const render::CameraView& cameraView,
                      GLRenderer& renderer) const override
            {}

            void reset() override {}

            [[nodiscard]] bool is2D() const override { return true; }
    };
} // namespace render
