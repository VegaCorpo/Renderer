#pragma once

#include "types/RenderDataBuffer.hpp"
#include "interfaces/IUIEngine.hpp"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace render {
    class ILayer {
        public:
            virtual ~ILayer() = default;

            // Init Methods
            virtual void init(GLFWwindow* window) = 0;

            // Render ImGUI Interface
            virtual void render() = 0;

            // Shutdown / cleanup
            virtual void shutdown() = 0;

    };
} // namespace ui
