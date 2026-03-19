#pragma once

#include <Camera3D.hpp>
#include <entt/entity/fwd.hpp>

namespace render {
    class RenderCamera {
        public:
            RenderCamera();
            ~RenderCamera() = default;

            void init();

            raylib::Camera getCamera() { return this->_camera; }

            void update();

            void addMovement(Vector3 dir);
            void addRotation(Vector2 rot);

            [[nodiscard]] bool isFollowing() const { return this->_isFollowing; }
            [[nodiscard]] entt::entity getFollowedEntity() const { return this->_followedEntity; }
            void stopFollowing() { this->_isFollowing = false; }
            void follow(entt::entity entity);
            void follow(Vector3 targetPos) { this->_camera.target = targetPos; }

        private:
            void _move();
            void _rotate();

            raylib::Camera _camera;

            Vector3 _movementDir;
            Vector2 _rotationDir;

            bool _isFollowing;
            entt::entity _followedEntity;

            static constexpr float MOVE_SPEED = 0.5f;
            static constexpr float ROTATION_SPEED = 0.02f;
    };
} // namespace render
