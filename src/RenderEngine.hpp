#pragma once

#include <raylib.h>
#include "IRenderEngine.hpp"

namespace render {
    constexpr const char* DEFAULT_TITLE = "Orbital Engine Renderer";

    class RenderEngine : public IRenderEngine {
        public:
            RenderEngine();
            ~RenderEngine();

            void init() override;

            [[nodiscard]] bool isRunning() const override { return this->_running; }

            void setUIBuffer(/* std::vector<UIElement*> uiElements */) override;

            void update() override;

        private:
            void render();

            bool _running = false;

            int _width;
            int _height;

            const int _fps;

            Camera _camera{};
    };
} // namespace render
