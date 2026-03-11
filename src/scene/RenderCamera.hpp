#pragma once

#include <Camera3D.hpp>

namespace render {
    class RenderCamera {
        public:
            RenderCamera();
            ~RenderCamera() = default;

            void init();

            raylib::Camera getCamera() { return this->_camera; }

            void addMovement(Vector3 dir);
            void addRotation(Vector2 rot);

            void update();

        private:
            void _move();
            void _rotate();

            raylib::Camera _camera;

            Vector3 _movementDir;
            Vector2 _rotationDir;

            static constexpr float MOVE_SPEED = 0.05f;
            static constexpr float ROTATION_SPEED = 0.02f;
    };
} // namespace render
