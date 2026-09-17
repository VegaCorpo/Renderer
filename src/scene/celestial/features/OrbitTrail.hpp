#pragma once

#include <unordered_map>
#include "IRenderFeature.hpp"
#include "LineDrawable.hpp"

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

                // Trails[entity] is default-constructed on first access, and owns its
                // own point buffer directly — no separate copy of the trail data.
                auto& points = _trails[entity].points();
                points.push_back(body.getScenePosition());

                if (points.size() > MAX_TRAIL_POINTS) {
                    points.erase(points.begin());
                }
            }

            void draw(entt::entity entity, const CelestialBody& body, const render::CameraView&,
                      GLRenderer& renderer) const override
            {
                auto it = _trails.find(entity);
                if (it == _trails.end())
                    return;

                it->second.setColor(body.getModelInfo()->dominantColor);
                it->second.draw(renderer, {});
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
            // mutable: draw() only refreshes the cached display color here,
            // it doesn't change which entities have a trail or their points.
            mutable std::unordered_map<entt::entity, LineDrawable> _trails;
    };
} // namespace render
