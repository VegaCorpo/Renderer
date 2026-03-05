#pragma once

#include <Camera3D.hpp>
#include <Model.hpp>
#include <Window.hpp>
#include <memory>
#include "IRenderEngine.hpp"

namespace render {
    constexpr const char* DEFAULT_TITLE = "Orbital Engine Renderer";
    constexpr int DEFAULT_WIDTH = 1280;
    constexpr int DEFAULT_HEIGHT = 800;
    constexpr int DEFAULT_FPS = 60;

    class RenderEngine : public IRenderEngine {
        public:
            RenderEngine();
            ~RenderEngine() = default;

            void init() override;

            [[nodiscard]] bool isRunning() const override { return this->_running; }

            void *getWindowHandle() override { return GetWindowHandle(); }

            void setVertexBuffer(/* std::vector<Vertex> vertexBuffer */) override;

            void update(entt::registry& registry) override;

            void render() override;

        private:
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
