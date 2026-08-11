#include <memory>
#include <queue>
#include "InputHandler.hpp"
#include "RenderEngine.hpp"
#include "types/types.hpp"

extern "C" {
    std::unique_ptr<common::IRenderEngine> get_engine()
    {
        return std::make_unique<render::RenderEngine>();
    }

    common::ModuleType get_module_type()
    {
        return common::ModuleType::RENDERER;
    }

    void updateActions(std::queue<common::Action>& actions)
    {
        inputs::InputHandler::updateActions(actions);
    }
}
