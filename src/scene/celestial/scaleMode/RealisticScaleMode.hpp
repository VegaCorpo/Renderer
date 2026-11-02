#pragma once

#include "IScaleMode.hpp"

namespace render {
    class RealisticScaleMode : public IScaleMode {
        public:
            // Real sizes are often below one pixel: the GPU may then cover no pixel center and skip the body
            static constexpr float MIN_PIXEL_RADIUS = 1.0f;

            RealisticScaleMode();

            void rescale(std::unordered_map<std::size_t, CelestialBody>& bodies) override;
            [[nodiscard]] float getMinPixelRadius() const override { return MIN_PIXEL_RADIUS; }

        private:
            bool _scaleComputed;
            float _distanceScale;

            void _applyScale(std::unordered_map<std::size_t, CelestialBody>& bodies) const;
            [[nodiscard]] static float
            _computeMaxDistance(const std::unordered_map<std::size_t, CelestialBody>& bodies);
    };
} // namespace render
