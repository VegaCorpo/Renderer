#pragma once

#include <raylib.h>
#include <Window.hpp>

namespace render {
    class RenderWindow : public raylib::Window {
        public:
            RenderWindow(int width, int height, const char* title, int fps);
            ~RenderWindow() = default;
    };
} // namespace render
