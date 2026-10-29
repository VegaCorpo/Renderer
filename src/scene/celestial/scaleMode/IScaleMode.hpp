#pragma once

#include <cstddef>
#include <unordered_map>
#include "CelestialBody.hpp"

namespace render {
    class IScaleMode {
        public:
            static constexpr float MAX_SCENE_DISTANCE = 100.f;
            virtual ~IScaleMode() = default;

            virtual void rescale(std::unordered_map<std::size_t, CelestialBody>& bodies) = 0;

            // Smallest on-screen radius in pixels a body is drawn with, 0 to always keep its real scale
            [[nodiscard]] virtual float getMinPixelRadius() const { return 0.0f; }
    };
} // namespace render
