#pragma once

#include "ARenderFeature.hpp"
#include "RenderMath.hpp"

namespace render {
    class CelestialIcons : public ARenderFeature {
        public:
            explicit CelestialIcons(std::shared_ptr<ARenderer>& renderer) : ARenderFeature(renderer) {}

            static constexpr int DEFAULT_FONT_SIZE = 12;

            void update(entt::entity entity, const CelestialBody& body) override {
            } //! to implement to save cameraview and if changed recompute icon

            void draw(entt::entity entity, const CelestialBody& body,
                      const render::CameraView& cameraView) const override
            {
                Vector3 pos = body.getScenePosition();

                auto screenWidth = static_cast<float>(this->_renderer->getWidth());
                auto screenHeight = static_cast<float>(this->_renderer->getHeight());

                Vector2 screenPos = Matrix4::GetWorldToScreen(pos, cameraView, screenWidth, screenHeight);

                // this->_renderer->drawText(body.getName().c_str(), static_cast<int>(screenPos.x),
                //                           static_cast<int>(screenPos.y), DEFAULT_FONT_SIZE,
                //                           body.getModelInfo()->dominantColor);
            }

            void reset() override {}

            [[nodiscard]] bool is2D() const override { return true; }
    };
} // namespace render
