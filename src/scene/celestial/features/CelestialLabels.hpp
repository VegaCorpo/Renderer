#pragma once

#include "IRenderFeature.hpp"

namespace render {
    class CelestialLabels : public IRenderFeature {
        public:
            static constexpr int DEFAULT_FONT_SIZE = 12;

            void update(entt::entity entity, const CelestialBody& body) override {}

            void render(entt::entity entity, const CelestialBody& body, const raylib::Camera& camera) const override
            {
                Vector3 pos = body.getScenePosition();

                Vector2 screenPos = GetWorldToScreen(pos, camera);

                DrawText(body.getName().c_str(), static_cast<int>(screenPos.x), static_cast<int>(screenPos.y),
                         DEFAULT_FONT_SIZE, body.getModelInfo()->dominantColor);
            }

            void reset() override {}

            [[nodiscard]] bool is2D() const override { return true; }
    };
} // namespace render
