#pragma once

#include "IScaleMode.hpp"

namespace render {
    class RealisticScaleMode : public IScaleMode {
        public:
            RealisticScaleMode();

            void rescale(std::unordered_map<std::size_t, CelestialBody>& bodies) override;

        private:
            bool _scaleComputed;
            float _distanceScale;

            void _applyScale(std::unordered_map<std::size_t, CelestialBody>& bodies) const;
            [[nodiscard]] static float
            _computeMaxDistance(const std::unordered_map<std::size_t, CelestialBody>& bodies);
    };
} // namespace render
