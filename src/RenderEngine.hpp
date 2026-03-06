#pragma once

#include <Camera3D.hpp>
#include <memory>
#include <Model.hpp>
#include <Window.hpp>
#include "interfaces/IRenderEngine.hpp"
#include "RenderDataHandler.hpp"

namespace render {
    constexpr const char* DEFAULT_TITLE = "Orbital Engine Renderer";
    constexpr int DEFAULT_WIDTH = 1280;
    constexpr int DEFAULT_HEIGHT = 800;
    constexpr int DEFAULT_FPS = 60;

    class RenderEngine : public common::IRenderEngine {
        public:
            RenderEngine();
            ~RenderEngine() = default;

            void init() override;

            [[nodiscard]] bool isRunning() const override { return this->_running; }

            void* getWindowHandle() override { return GetWindowHandle(); }

            void setVertexBuffer(common::RenderDataBuffer& renderDataBuffer) override;

            void update(entt::registry& registry) override;

            void render() override;

        private:
            bool _running = false;

            int _width;
            int _height;

            int _fps;

            std::unique_ptr<raylib::Window> _window;
            raylib::Camera _camera{};

            RenderDataHandler _renderDataHandler;

            std::unique_ptr<raylib::Model> _sphere;
            std::unique_ptr<raylib::Model> _plane;
    };
} // namespace render
