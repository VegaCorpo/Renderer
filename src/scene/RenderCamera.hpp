#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include "RenderTypes.hpp"

namespace render {
    class RenderCamera {
        public:
            RenderCamera();
            ~RenderCamera() = default;

            void init();

            [[nodiscard]] render::CameraView getCameraView() const { return this->_cameraView; }

            void update();

            void addMovement(Eigen::Vector3f dir);
            void addRotation(Eigen::Vector3f rot);

            /**
             * @brief Rotate the camera instantly from a mouse delta (in pixels)
             */
            void addMouseRotation(float deltaX, float deltaY);

            [[nodiscard]] bool isFollowing() const { return this->_followedEntity != SIZE_MAX; }
            [[nodiscard]] std::size_t getFollowedEntity() const { return this->_followedEntity; }

            [[nodiscard]] bool isZooming() const { return this->_zooming; }

            /**
             * @brief Start following an entity, SIZE_MAX to stop
             *
             * Starts a zoom on the entity, or on the whole scene when following stops.
             */
            void follow(std::size_t entity = SIZE_MAX);

            /**
             * @brief Move the camera along with the followed entity
             */
            void updateFollow(const Eigen::Vector3f& entityPos);

            /**
             * @brief Smoothly move the camera to frame the bounds, ends the zoom once framed
             */
            void updateZoom(const BoundingSphere& bounds);
            void cancelZoom() { this->_zooming = false; }

        private:
            void _move();
            void _rotate();
            void _applyRotation(float yaw, float pitch, float roll);

            render::CameraView _cameraView;

            Eigen::Vector3f _movementDir;
            Eigen::Vector3f _rotationDir;

            std::size_t _followedEntity;
            std::optional<Eigen::Vector3f> _lastFollowedPos;
            bool _zooming;

            static constexpr float MOVE_SPEED = 0.5f;
            static constexpr float ROTATION_SPEED = 0.02f;
            static constexpr float MOUSE_SENSITIVITY = 0.003f; // radians per pixel
            static constexpr float ZOOM_SMOOTHING = 0.1f; // fraction of the remaining path done each frame
            static constexpr float ZOOM_END_RATIO = 0.01f; // zoom ends when closer than 1% of the distance
            static constexpr float ENTITY_ZOOM_MARGIN = 3.0f; // the entity takes 1/3 of the screen height
            static constexpr float SCENE_ZOOM_MARGIN = 1.2f;
            static constexpr float MIN_ZOOM_DISTANCE = 0.5f; // stays beyond the near plane (0.1)
    };
} // namespace render
