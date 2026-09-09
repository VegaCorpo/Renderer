#pragma once

#include "IScaleMode.hpp"
#include <Eigen/Dense>

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
            [[nodiscard]] Eigen::Vector3f _logPositionScale(const Eigen::Vector3f& realPosition, float maxDistance) const;
    };

} // namespace render
