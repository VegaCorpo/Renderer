#pragma once

#include <array>
#include <bitset>
#include <cstddef>
#include <functional>
#include <optional>
#include <types/World.hpp>
#include <unordered_map>
#include "CelestialBody.hpp"
#include "IRenderFeature.hpp"
#include "RealisticScaleMode.hpp"
#include "ResourceManager.hpp"
#include "VisualScaleMode.hpp"

namespace render {
    class CelestialManager {
        public:
            enum class ScaleMode { VISUAL, REALISTIC, SCALE_MODE_NUMBER };
            enum class Feature { TRAILS, LABELS, ICONS, FEATURE_NUMBER };

            explicit CelestialManager(std::shared_ptr<GLRenderer>& renderer);
            ~CelestialManager() = default;

            void changeScaleMode();
            void toggleFeature(Feature feature);
            void setScaleMode(ScaleMode mode) { _scaleMode = mode; }
            void setVisualScaleConfig(const VisualScaleMode::VisualScaleConfig& config) { _visualConfig = config; }

            void initBodies(const common::SpecificDataRender& data);
            void updateBodies(const common::SpecificDataRender& data);
            void syncIn(const common::WorldState& world);
            void update();

            const std::unordered_map<std::size_t, CelestialBody>& bodies() const { return _bodies; }

            [[nodiscard]] std::optional<BoundingSphere> getBodyBounds(std::size_t entity) const;
            [[nodiscard]] std::optional<BoundingSphere> getSceneBounds() const;

            void render3D(const render::CameraView& cameraView) const;
            void render2D(const render::CameraView& cameraView) const;

        private:
            void _updateScaleStrategy();
            [[nodiscard]] bool _hasBodiesBeenModified();
            void _drawBodyFeatures(std::size_t entity, const CelestialBody& body, const CameraView& cameraView) const;
            [[nodiscard]] static Eigen::Matrix4f _buildModelMatrix(const CelestialBody& body);
            [[nodiscard]] static const Eigen::Quaternionf& _meshToBodyFrame();
            [[nodiscard]] static const Eigen::Quaternionf& _physicsToRenderFrame();

            template <typename Func>
            void _forEachEnabledFeature(Func&& func) const;

            std::shared_ptr<GLRenderer> _renderer;

            std::unique_ptr<ResourceManager> _resourceManager;

            std::unordered_map<std::size_t, CelestialBody> _bodies;
            std::unordered_map<TextureHandle, std::vector<std::size_t>> _batchesByTexture;

            // Biggest body: emits the scene light and is drawn unlit
            std::optional<std::size_t> _lightSource;

            ScaleMode _scaleMode;
            std::unique_ptr<IScaleMode> _scaleStrategy;
            VisualScaleMode::VisualScaleConfig _visualConfig;

            static constexpr std::size_t FEATURE_COUNT = static_cast<std::size_t>(Feature::FEATURE_NUMBER);

            // Indexed by Feature, nullptr when the feature isn't implemented yet
            std::array<std::unique_ptr<IRenderFeature>, FEATURE_COUNT> _features;
            std::bitset<FEATURE_COUNT> _enabledFeatures;

            const std::unordered_map<ScaleMode, std::function<std::unique_ptr<IScaleMode>()>> _scaleModes = {
                {ScaleMode::REALISTIC, [this]() { return std::make_unique<RealisticScaleMode>(); }},
                {ScaleMode::VISUAL, [this]() { return std::make_unique<VisualScaleMode>(this->_visualConfig); }},
            };
    };
} // namespace render
