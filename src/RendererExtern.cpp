#include "RenderEngine.hpp"
#include "types/types.hpp"
#include <iostream>
#include <memory>

extern "C++" {
    std::unique_ptr<render::IRenderEngine> get_render_engine()
    {
        std::cout << "Hello from render engine" << std::endl;
        return std::make_unique<render::RenderEngine>();
    }

    common::ModuleType get_module_type()
    {
        return common::ModuleType::RENDERER;
    }
}
