#pragma once

#include <entt/entt.hpp>
#include <memory>
#include <Model.hpp>
#include <raylib.h>
#include <unordered_map>
#include "CelestialBody.hpp"
#include "scaleMode/RealisticScaleMode.hpp"
#include "scaleMode/VisualScaleMode.hpp"

namespace render {

    class CelestialManager {
        public:
            enum class ScaleMode { VISUAL, REALISTIC, SCALE_MODE_NUMBER };

            CelestialManager();
            ~CelestialManager() = default;

            void setScaleMode(ScaleMode mode) { _scaleMode = mode; }
            void setVisualScaleConfig(const VisualScaleMode::VisualScaleConfig& config) { _visualConfig = config; }

            void addOrUpdateBody(entt::entity entity, const std::string& name, const Vector3& realPosition,
                                 float realRadiusKm, Color color, std::shared_ptr<raylib::Model>& model);

            void update(entt::registry& registry);

            const std::unordered_map<entt::entity, CelestialBody>& bodies() const { return _bodies; }

            void render() const;

        private:
            void _updateScaleStrategy() { this->_scaleStrategy = this->_scaleModes.at(this->_scaleMode)(); }
            [[nodiscard]] bool _hasBodiesBeenModified();

            std::unordered_map<entt::entity, CelestialBody> _bodies;

            ScaleMode _scaleMode;
            VisualScaleMode::VisualScaleConfig _visualConfig;

            std::unique_ptr<IScaleMode> _scaleStrategy;

            std::shared_ptr<raylib::Model> _sphereModel;
            Texture2D _defaultTexture;

            const std::unordered_map<ScaleMode, std::function<std::unique_ptr<IScaleMode>()>> _scaleModes = {
                {ScaleMode::REALISTIC, [this]() { return std::make_unique<RealisticScaleMode>(); }},
                {ScaleMode::VISUAL, [this]() { return std::make_unique<VisualScaleMode>(this->_visualConfig); }},
            };
    };
} // namespace render
