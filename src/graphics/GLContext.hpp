#pragma once

#include "RenderTypes.hpp"

struct GLFWwindow;

namespace render {
    class GLContext {
        public:
            GLContext() = default;
            ~GLContext();

            GLContext(const GLContext&) = delete;
            GLContext& operator=(const GLContext&) = delete;

            [[nodiscard]] bool create(const RendererConfig& config);
            void destroy();

            void pollEvents() const;
            void swapBuffers() const;

            [[nodiscard]] bool shouldClose() const;
            void requestClose() const;

            [[nodiscard]] int getWidth() const { return this->_width; }
            [[nodiscard]] int getHeight() const { return this->_height; }

            [[nodiscard]] void* getNativeHandle() const;

        private:
            static void _framebufferSizeCallback(GLFWwindow* window, int width, int height);

            GLFWwindow* _window = nullptr;
            int _width = 0;
            int _height = 0;
    };
} // namespace render
