#pragma once

#include <entt/entity/fwd.hpp>
#include "renderer/RenderTypes.hpp"

namespace render {
    class RenderCamera {
        public:
            RenderCamera();
            ~RenderCamera() = default;

            void init();

            [[nodiscard]] render::CameraView getCameraView() const { return this->_cameraView; }

            void update();

            void addMovement(Vector3 dir);
            void addRotation(Vector3 rot);

            [[nodiscard]] bool isFollowing() const { return this->_isFollowing; }
            [[nodiscard]] entt::entity getFollowedEntity() const { return this->_followedEntity; }

            void follow(entt::entity entity);
            void follow(Vector3 targetPos) { this->_cameraView.target = targetPos; }
            void stopFollowing() { this->_isFollowing = false; }

        private:
            void _move();
            void _rotate();

            render::CameraView _cameraView;

            Vector3 _movementDir;
            Vector3 _rotationDir;

            bool _isFollowing;
            entt::entity _followedEntity;

            static constexpr float MOVE_SPEED = 0.5f;
            static constexpr float ROTATION_SPEED = 0.02f;
    };
} // namespace render
