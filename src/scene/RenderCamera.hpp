#pragma once

#include <Camera3D.hpp>

namespace render {
    class RenderCamera {
        public:
            RenderCamera();
            ~RenderCamera() = default;

            void init();

            raylib::Camera getCamera() { return this->_camera; }

            void update();

        private:
            raylib::Camera _camera;
    };
} // namespace render
