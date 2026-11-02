#include <memory>
#include <queue>
#include "RenderEngine.hpp"
#include "types/ModuleInfo.hpp"
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

    const common::ModuleInfo* get_module_info()
    {
        static constexpr common::ModuleInfo info {
            .name = ORBITAL_MODULE_NAME,
            .version = ORBITAL_MODULE_VERSION,
            .type = common::ModuleType::RENDERER,
        };
        return &info;
    }

    void updateActions(std::queue<common::Action>& actions)
    {
        // inputs::InputHandler::updateActions(actions);
    }
}
