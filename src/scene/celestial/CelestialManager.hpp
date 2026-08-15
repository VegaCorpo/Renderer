#pragma once

#include <components/position.hpp>
#include <components/radius.hpp>
#include <entt/entt.hpp>
#include <vector>
#include "ARenderFeature.hpp"
#include "CelestialBody.hpp"
#include "RealisticScaleMode.hpp"
#include "ResourceManager.hpp"
#include "VisualScaleMode.hpp"

namespace render {
    class CelestialManager {
        public:
            enum class ScaleMode { VISUAL, REALISTIC, SCALE_MODE_NUMBER };

            explicit CelestialManager(std::shared_ptr<ARenderer>& renderer);
            ~CelestialManager() = default;

            void changeScaleMode();
            void setScaleMode(ScaleMode mode) { _scaleMode = mode; }
            void setVisualScaleConfig(const VisualScaleMode::VisualScaleConfig& config) { _visualConfig = config; }

            void syncIn(entt::registry& registry);
            void update();

            const std::unordered_map<entt::entity, CelestialBody>& bodies() const { return _bodies; }

            render::Vector3 getBodyPosition(entt::entity entity) const;

            void render3D(const render::CameraView& cameraView) const;
            void render2D(const render::CameraView& cameraView) const;

        private:
            void _addOrUpdateBody(entt::entity entity, entt::registry& registry, common::components::Position pos,
                                  common::components::Radius radius);

            void _updateScaleStrategy();
            [[nodiscard]] bool _hasBodiesBeenModified();

            std::shared_ptr<ARenderer> _renderer;

            std::unique_ptr<ResourceManager> _resourceManager;

            std::unordered_map<entt::entity, CelestialBody> _bodies;

            ScaleMode _scaleMode;
            std::unique_ptr<IScaleMode> _scaleStrategy;
            VisualScaleMode::VisualScaleConfig _visualConfig;

            std::vector<std::unique_ptr<ARenderFeature>> _features;

            const std::unordered_map<ScaleMode, std::function<std::unique_ptr<IScaleMode>()>> _scaleModes = {
                {ScaleMode::REALISTIC, [this]() { return std::make_unique<RealisticScaleMode>(); }},
                {ScaleMode::VISUAL, [this]() { return std::make_unique<VisualScaleMode>(this->_visualConfig); }},
            };
    };
} // namespace render
