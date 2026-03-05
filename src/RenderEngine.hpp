#pragma once

#include <Camera3D.hpp>
#include <Model.hpp>
#include <Window.hpp>
#include <memory>
#include "IRenderEngine.hpp"

namespace render {
    constexpr const char* DEFAULT_TITLE = "Orbital Engine Renderer";

    class RenderEngine : public IRenderEngine {
        public:
            RenderEngine();
            ~RenderEngine() = default;

            void init() override;

            [[nodiscard]] bool isRunning() const override { return this->_running; }

            void setVertexBuffer(/* std::vector<Vertex> vertexBuffer */) override;

            void update() override;

        private:
            void render();

            bool _running = false;

            int _width;
            int _height;

            int _fps;

            std::unique_ptr<raylib::Window> _window;
            raylib::Camera _camera{};

            std::unique_ptr<raylib::Model> _sphere;
            std::unique_ptr<raylib::Model> _plane;
    };
} // namespace render
