#pragma once

#include <cstddef>
#include <unordered_map>
#include "ADisplayOption.hpp"
#include "LineDrawable.hpp"

namespace render {
    class OrbitTrail : public ADisplayOption {
        public:
            static constexpr const char* NAME = "Trails";
            static constexpr const char* DESCRIPTION = "Draws the path followed by each body";

            static constexpr const char* PARAM_MAX_POINTS = "max_points";
            static constexpr const char* PARAM_MAX_POINTS_DESCRIPTION = "Maximum number of points in a trail";
            static constexpr const char* PARAM_MIN_DISTANCE = "min_distance";
            static constexpr const char* PARAM_MIN_DISTANCE_DESCRIPTION =
                "Minimum distance between two points of the trail, in scene units";

            // Scene units, the scene fits in IScaleMode::MAX_SCENE_DISTANCE
            static constexpr float DEFAULT_MIN_DISTANCE = 1.f;
            static constexpr std::size_t MAX_TRAIL_POINTS = 500;
            static constexpr std::size_t MIN_TRAIL_POINTS = 2;

            explicit OrbitTrail(float minDistance = DEFAULT_MIN_DISTANCE);

            void update(std::size_t entity, const CelestialBody& body) override;
            void draw(std::size_t entity, const CelestialBody& body, const render::CameraView& cameraView,
                      GLRenderer& renderer) const override;
            void reset() override;

        private:
            std::size_t _maxTrailPoints;
            float _minDistance;

            mutable std::unordered_map<std::size_t, LineDrawable> _trails;
    };
} // namespace render
