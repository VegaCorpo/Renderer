#include "RenderEngine.hpp"
#include "InputHandler.hpp"
#include "RaylibRenderer.hpp"
#include "RenderActions.hpp"
#include "RenderTypes.hpp"

render::RenderEngine::RenderEngine() : _running(false), _drawUI(true), _renderer(std::make_shared<RaylibRenderer>()), _scene(nullptr)
{}

void render::RenderEngine::init()
{
    this->_renderer->initialize(RendererConfig());

    this->_scene = std::make_unique<Scene>();
    this->_scene->init(this->_renderer);

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
    if (!this->_running || !this->_scene)
        return;

    if (this->_renderer->windowShouldClose()) {
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
    if (!this->_running || !this->_renderer || !this->_scene) {
        return;
    }

    this->_renderer->beginFrame();
    this->_renderer->clear(Color::Black());

    this->_scene->render();

    if (this->_drawUI && uiRender) {
        uiRender();
    }

    this->_renderer->endFrame();
}
