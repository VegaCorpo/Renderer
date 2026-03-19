#pragma once

#include "interfaces/IUIEngine.hpp"
#include "ILayer.hpp"
#include <memory>
#include <types/RenderDataBuffer.hpp>

namespace render {

    // Core UI engine interface responsible for generating render data.
    class UIEngine : public common::IUIEngine {
        public:
            ~UIEngine() = default;

            void init(void* window) override;
            
            // Update UI frame and convert it for the renderer
            void update(float dt, float w, float h) override;
            
            common::RenderDataBuffer getDataBuffer() override { return this->_renderBuffer; }

            void render() override;
        private:

            template<typename TLayer>
            void _initWithLayer(GLFWwindow* window);
            // Internal buffer containing all UI geometry and commands
            common::RenderDataBuffer _renderBuffer;

            // Layer depending on the GUI you want to use
            std::unique_ptr<render::ILayer> _layer = nullptr;
    };

} // namespace ui