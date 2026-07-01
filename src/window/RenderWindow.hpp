#pragma once

#include <raylib.h>
#include <Window.hpp>

namespace render {
    class RenderWindow : public raylib::Window {
        public:
            RenderWindow(int width, int height, const std::string &title, int fps, TraceLogLevel logLevel);
            ~RenderWindow() = default;
    };
} // namespace render
