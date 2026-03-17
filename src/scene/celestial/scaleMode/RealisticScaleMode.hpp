#pragma once

#include "IScaleMode.hpp"

namespace render {
    class RealisticScaleMode : public IScaleMode {
        public:
            void rescale(std::unordered_map<entt::entity, CelestialBody>& bodies) override;
    };
} // namespace render
