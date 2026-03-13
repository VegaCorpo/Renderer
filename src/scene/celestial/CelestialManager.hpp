#pragma once

#include <entt/entt.hpp>
#include <memory>
#include <Model.hpp>
#include <unordered_map>
#include "CelestialBody.hpp"

namespace render {

    class CelestialManager {
        public:
            enum class ScaleMode { VISUAL, REALISTIC, SCALE_MODE_NUMBER };

            enum class SizeAlgo { LOG };
            enum class PositionAlgo { LOG };

            struct VisualScaleConfig {
                    float logBoostFactor = 10.0f; // k : plus k est grand, plus les petits corps sont boostés
                    float maxVisualRadius = 5.0f; // rayon max dans la scène (unités raylib)
                    float maxVisualDistance = 100.0f; // distance max dans la scène (unités raylib)
                    float minVisualRadius = 0.3f; // taille minimum garantie pour tout corps
                    SizeAlgo sizeAlgo = SizeAlgo::LOG;
                    PositionAlgo positionAlgo = PositionAlgo::LOG;
            };

            CelestialManager();
            ~CelestialManager() = default;

            void setScaleMode(ScaleMode mode) { _scaleMode = mode; }
            void setVisualScaleConfig(const VisualScaleConfig& config) { _visualConfig = config; }

            void addOrUpdateBody(entt::entity entity, const std::string& name, const Vector3& realPosition,
                                 float realRadiusKm, Color color, std::shared_ptr<raylib::Model>& model);

            void update(entt::registry& registry);

            const std::unordered_map<entt::entity, CelestialBody>& bodies() const { return _bodies; }

            void render() const;

        private:
            [[nodiscard]] bool _hasBodiesBeenModified();

            // Rescale modes
            void _realisticRescale();
            void _visualRescale();

            // Visual rescale internals
            void _computeVisualSizeScale();
            void _computeVisualPositionScale();

            // Swappable algos — taille
            [[nodiscard]] float _logSizeScale(float realRadius, float maxRadius) const;

            // Swappable algos — position
            [[nodiscard]] Vector3 _logPositionScale(const Vector3& realPosition, float maxDistance) const;

            std::unordered_map<entt::entity, CelestialBody> _bodies;

            ScaleMode _scaleMode;
            VisualScaleConfig _visualConfig;

            const std::unordered_map<ScaleMode, std::function<void()>> _scaleModeFunctions = {
                {ScaleMode::VISUAL, [this] { this->_visualRescale(); }},
                {ScaleMode::REALISTIC, [this] { this->_realisticRescale(); }},
            };

            std::shared_ptr<raylib::Model> _sphereModel;
    };
} // namespace render
