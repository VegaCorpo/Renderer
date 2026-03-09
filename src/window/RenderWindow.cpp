#include "RenderWindow.hpp"

render::RenderWindow::RenderWindow(int width, int height, const char* title, int fps) :
    raylib::Window(raylib::Window(width, height, title))
{
    this->SetTargetFPS(fps);
}
