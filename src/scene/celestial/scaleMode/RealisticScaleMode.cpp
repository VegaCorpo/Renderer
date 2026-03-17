#include "RealisticScaleMode.hpp"
#include "SolarSystemValues.hpp"

void render::RealisticScaleMode::rescale(std::unordered_map<entt::entity, CelestialBody>& bodies)
{
    for (auto& [entity, body] : bodies) {
        body.computePositionAndScale(SCALE);
    }
}
