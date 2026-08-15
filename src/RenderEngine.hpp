#pragma once

#include <memory>
#include <queue>
#include "GLFW/glfw3.h"
#include "interfaces/IRenderEngine.hpp"
#include "renderer/ARenderer.hpp"
#include "Scene.hpp"

namespace render {
    class RenderEngine : public common::IRenderEngine {
        public:
            RenderEngine();
            ~RenderEngine() = default;

            void init() override;

            [[nodiscard]] bool isRunning() const override { return this->_running; }

            unsigned int loadTextureFromPixels(unsigned char* pixels, int width, int height) override { return 0; }

            void* getWindowHandle() override { return glfwGetCurrentContext(); }

            void setVertexBuffer(common::RenderDataBuffer& buffer) override;

            void handleActions(std::queue<common::Action>& actions); //! override

            void syncIn(entt::registry& registry) override;
            void update() override;

            void render(std::function<void()> uiRender) override;

        private:
            bool _running;
            bool _drawUI;

            std::shared_ptr<ARenderer> _renderer;

            std::unique_ptr<Scene> _scene;
    };
} // namespace render
