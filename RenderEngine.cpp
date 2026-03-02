#include "RenderEngine.hpp"
#include <iostream>
#include <memory>

extern "C++" {
std::unique_ptr<render::RenderEngine> get_render_engine()
{
    std::cout << "Hello from render engine" << std::endl;
    return std::make_unique<render::RenderEngine>();
}
}
