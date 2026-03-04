#include "RenderEngine.hpp"
#include "types/types.hpp"

static render::RenderEngine renderer;

extern "C++" {
    void init() { renderer.init(); }

    bool is_running() { return renderer.isRunning(); }

    void set_ui_buffer(/* std::vector<UIElement*> uiElements */) { renderer.setUIBuffer(); }

    void update() { renderer.update(); }

    common::ModuleType get_module_type() { return common::ModuleType::RENDERER; }
}
