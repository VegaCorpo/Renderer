#include "RenderEngine.hpp"

render::RenderEngine::RenderEngine() : _running(false), _renderDataHandler(), _window(nullptr), _scene(nullptr)
{}

void render::RenderEngine::init()
{
    // Disable Raylib logs
    SetTraceLogLevel(LOG_NONE);

    this->_window = std::make_unique<RenderWindow>(DEFAULT_WIDTH, DEFAULT_HEIGHT, DEFAULT_TITLE, DEFAULT_FPS);

    this->_scene = std::make_unique<Scene>();
    this->_scene->init();

    this->_running = true;
}

void render::RenderEngine::setVertexBuffer(common::RenderDataBuffer& buffer)
{
    this->_renderDataHandler.update(buffer);
}

void render::RenderEngine::update(entt::registry& /*registry*/)
{
    if (this->_window->ShouldClose()) {
        this->_running = false;
    }

    if (this->_scene) {
        this->_scene->update();
    }

    this->render();
}

void render::RenderEngine::render()
{
    if (!this->_running || !this->_window || !this->_scene)
        return;

    this->_window->BeginDrawing();
    this->_window->ClearBackground(DARKBLUE);

    BeginMode3D(this->_scene->getCamera());

    this->_scene->render();

    EndMode3D();

    this->_window->DrawFPS();

    this->_window->EndDrawing();
}
