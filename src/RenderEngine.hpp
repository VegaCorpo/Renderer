#pragma once

#include <memory>
#include <queue>
#include "interfaces/IRenderEngine.hpp"
#include "RenderDataHandler.hpp"
#include "RenderWindow.hpp"
#include "Scene.hpp"

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

            void setVertexBuffer(common::RenderDataBuffer& buffer) override;

            void handleActions(std::queue<common::Action>& actions); //! override

            void update(entt::registry& registry) override;

            void render() override;

        private:
            bool _running = false;

            RenderDataHandler _renderDataHandler;

            std::unique_ptr<RenderWindow> _window;
            std::unique_ptr<Scene> _scene;
    };
} // namespace render
