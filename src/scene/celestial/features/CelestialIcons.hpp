#pragma once

#include "IRenderFeature.hpp"
#include "TextDrawable.hpp"

namespace render {
    class CelestialIcons : public IRenderFeature {
        public:
            static constexpr int DEFAULT_FONT_SIZE = 12;

            void update(entt::entity entity, const CelestialBody& body) override {
            } //! to implement to save cameraview and if changed recompute icon

            void draw(entt::entity entity, const CelestialBody& body, const render::CameraView& cameraView,
                      GLRenderer& renderer) const override
            {
                // Eigen::Vector3f pos = body.getScenePosition();

                // auto screenWidth = static_cast<float>(renderer.getWidth());
                // auto screenHeight = static_cast<float>(renderer.getHeight());

                // Eigen::Vector2f screenPos = worldToScreen(pos, cameraView, screenWidth, screenHeight);

                // TextDrawable(body.getName(), body.getModelInfo()->dominantColor)
                //     .draw(renderer, {{screenPos.x(), screenPos.y(), 0.0f}, 1.0f});
            }

            void reset() override {}

            [[nodiscard]] bool is2D() const override { return true; }
    };
} // namespace render
