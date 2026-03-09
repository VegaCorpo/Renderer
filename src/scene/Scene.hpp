#pragma once

#include <Camera3D.hpp>
#include <memory>
#include <Model.hpp>
#include "RenderCamera.hpp"

namespace render {
    class Scene {
        public:
            Scene();
            ~Scene() = default;

            void init();

            raylib::Camera getCamera() { return this->_camera->getCamera(); }

            void update();

            void render();

        private:
            std::unique_ptr<render::RenderCamera> _camera;

            std::unique_ptr<raylib::Model> _sphere;
            std::unique_ptr<raylib::Model> _plane;
    };
} // namespace render
