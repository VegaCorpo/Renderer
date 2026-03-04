#pragma once

#include <raylib.h>

namespace render {
    constexpr const char* DEFAULT_TITLE = "Orbital Engine Renderer";

    class RenderEngine {
        public:
            RenderEngine();
            ~RenderEngine();

            void init();

            [[nodiscard]] bool isRunning() const { return this->_running; }

            void setUIBuffer(/* std::vector<UIElement*> uiElements */);

            void update();

        private:
            void render();

            bool _running = false;

            int _width;
            int _height;

            const int _fps;

            const char* _title;

            Camera _camera{};
    };
} // namespace render
