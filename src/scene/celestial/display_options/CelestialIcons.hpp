#pragma once

#include "ADisplayOption.hpp"

namespace render {
    class CelestialIcons : public ADisplayOption {
        public:
            static constexpr const char* NAME = "Icons";
            static constexpr const char* DESCRIPTION = "Displays an icon on each body";

            CelestialIcons();

            void update(std::size_t entity, const CelestialBody& body) override;
            void draw(std::size_t entity, const CelestialBody& body, const render::CameraView& cameraView,
                      GLRenderer& renderer) const override;
            void reset() override;
    };
} // namespace render
