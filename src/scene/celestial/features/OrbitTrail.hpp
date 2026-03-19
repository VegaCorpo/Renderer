#pragma once

#include "IRenderFeature.hpp"

namespace render {
    class OrbitTrail : public IRenderFeature {
        public:
            static constexpr int DEFAULT_UPDATE_INTERVAL = 10;
            static constexpr size_t MAX_TRAIL_POINTS = 1000;

            explicit OrbitTrail(int updateInterval = DEFAULT_UPDATE_INTERVAL) : _updateInterval(updateInterval) {}

            void update(entt::entity entity, const CelestialBody& body) override
            {
                auto& counter = _updateCounters[entity];
                counter++;

                if (counter < _updateInterval)
                    return;

                counter = 0;

                _trails[entity].push_back(body.getScenePosition());

                if (_trails[entity].size() > MAX_TRAIL_POINTS) {
                    _trails[entity].erase(_trails[entity].begin());
                }
            }

            void render(entt::entity entity, const CelestialBody& body, const raylib::Camera&) const override
            {
                auto it = _trails.find(entity);
                if (it == _trails.end())
                    return;

                const auto& trail = it->second;
                if (trail.size() < 2)
                    return;

                const size_t total = trail.size();

                for (size_t i = 1; i < total; i++) {
                    float t = static_cast<float>(i) / static_cast<float>(total - 1);

                    DrawLine3D(trail[i - 1], trail[i], body.getModelInfo()->dominantColor);
                }
            }

            void reset() override
            {
                _trails.clear();
                _updateCounters.clear();
            }

            [[nodiscard]] bool is2D() const override { return false; }

        private:
            int _updateInterval;

            std::unordered_map<entt::entity, int> _updateCounters;
            std::unordered_map<entt::entity, std::vector<Vector3>> _trails;
    };
} // namespace render
