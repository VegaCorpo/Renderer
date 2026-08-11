#include "RenderEngine.hpp"
#include <raylib.h>
#include "InputHandler.hpp"
#include "RenderActions.hpp"

render::RenderEngine::RenderEngine() : _running(false), _drawUI(true), _window(nullptr), _scene(nullptr)
{}

void render::RenderEngine::init()
{
    this->_window =
        std::make_unique<RenderWindow>(DEFAULT_WIDTH, DEFAULT_HEIGHT, DEFAULT_TITLE, DEFAULT_FPS, LOG_LEVEL);

    this->_scene = std::make_unique<Scene>();
    this->_scene->init();

    this->_running = true;
}

void render::RenderEngine::setVertexBuffer(common::RenderDataBuffer& buffer)
{}

void render::RenderEngine::handleActions(std::queue<common::Action>& actions)
{
    std::queue<common::Action> remaining;

    while (!actions.empty()) {
        common::Action action = actions.front();
        actions.pop();

        bool consumed = false;

        if (this->_scene && std::ranges::find(render::sceneActions, action) != render::sceneActions.end()) {
            this->_scene->handleAction(action);
            consumed = true;
        }

        if (!consumed) {
            remaining.push(action);
        }
    }

    actions = std::move(remaining);
}

void render::RenderEngine::syncIn(entt::registry& registry)
{
    if (this->_scene) {
        this->_scene->syncIn(registry);
    }
}

void render::RenderEngine::update()
{
    if (!this->_running || !this->_window || !this->_scene)
        return;

    if (this->_window->ShouldClose()) { // NOLINT(readability-static-accessed-through-instance)
        this->_running = false;
        return;
    }

    //! to remove when inputs will be handle in "Inputs" module
    std::queue<common::Action> actions = {};
    inputs::InputHandler::updateActions(actions);
    this->handleActions(actions);

    this->_scene->update();
}

void render::RenderEngine::render(std::function<void()> uiRender)
{
    if (!this->_running || !this->_window || !this->_scene) {
        return;
    }

    this->_window->BeginDrawing();
    this->_window->ClearBackground();

    this->_scene->render();

    if (this->_drawUI && uiRender) {
        uiRender();
    }

    this->_window->EndDrawing();
}
