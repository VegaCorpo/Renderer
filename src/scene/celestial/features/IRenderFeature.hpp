#pragma once

#include <Camera3D.hpp>
#include <entt/entt.hpp>
#include "CelestialBody.hpp"

namespace render {
    class IRenderFeature {
        public:
            virtual ~IRenderFeature() = default;

            virtual void update(entt::entity entity, const CelestialBody& body) = 0;
            virtual void render(entt::entity entity, const CelestialBody& body, const raylib::Camera& camera) const = 0;

            virtual void reset() = 0;
    };
} // namespace render
