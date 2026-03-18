#pragma once

#include <entt/entity/fwd.hpp>
#include <unordered_map>
#include "CelestialBody.hpp"

namespace render {
    class IScaleMode {
        public:
            virtual ~IScaleMode() = default;

            virtual void rescale(std::unordered_map<entt::entity, CelestialBody>& bodies) = 0;
    };
} // namespace render
