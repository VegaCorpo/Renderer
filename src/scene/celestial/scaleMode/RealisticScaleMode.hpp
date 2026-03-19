#pragma once

#include "IScaleMode.hpp"

namespace render {
    class RealisticScaleMode : public IScaleMode {
        public:
            RealisticScaleMode();

            void rescale(std::unordered_map<entt::entity, CelestialBody>& bodies) override;

        private:
            bool _scaleComputed;
            float _distanceScale;

            void _applyScale(std::unordered_map<entt::entity, CelestialBody>& bodies) const;
            [[nodiscard]] static float
            _computeMaxDistance(const std::unordered_map<entt::entity, CelestialBody>& bodies);
    };
} // namespace render
