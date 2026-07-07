#include "RenderWindow.hpp"

render::RenderWindow::RenderWindow(int width, int height, const std::string &title, int fps, TraceLogLevel logLevel) :
    raylib::Window(width, height, title, 0, logLevel)
{
    this->SetTargetFPS(fps);
}
