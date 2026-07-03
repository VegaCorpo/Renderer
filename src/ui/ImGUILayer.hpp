#pragma once

#include <imgui.h>
#include "ILayer.hpp"

namespace render {
    class ImGUILayer : public render::ILayer {
        public:
            ImGUILayer() : _isShutdown(false) {};
            ~ImGUILayer() override
            {
                if (!this->_isShutdown) {
                    this->shutdown();
                }
            };

            void init(GLFWwindow* window) override;

            void render() override;

            void shutdown() override;

        private:
            // GUI Interface Methods
            void _setupStyle();
            void _mainMenu();

            // Private Attributs
            common::RenderDataBuffer _buffer;
            GLFWwindow* _window = nullptr;
            bool _isShutdown;
            unsigned int _fontTextureId = 0;
    };
} // namespace render
