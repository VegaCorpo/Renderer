#pragma once

#include "IScaleMode.hpp"

namespace render {

    class VisualScaleMode : public IScaleMode {
        public:
            enum class SizeAlgo { LOG };
            enum class PositionAlgo { LOG };

            struct VisualScaleConfig {
                    float logBoostFactor = 10.0f;
                    float maxVisualRadius = 5.0f;
                    float maxVisualDistance = 100.0f;
                    float minVisualRadius = 0.3f;
                    SizeAlgo sizeAlgo = SizeAlgo::LOG;
                    PositionAlgo positionAlgo = PositionAlgo::LOG;
            };

            explicit VisualScaleMode(const VisualScaleConfig& config);

            void rescale(std::unordered_map<entt::entity, CelestialBody>& bodies) override;

        private:
            VisualScaleConfig _config;

            [[nodiscard]] float _logSizeScale(float realRadius, float maxRadius) const;
            [[nodiscard]] Vector3 _logPositionScale(const Vector3& realPosition, float maxDistance) const;
    };

} // namespace render
