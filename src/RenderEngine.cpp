#include "RenderEngine.hpp"
#include <raylib.h>
#include "InputHandler.hpp"
#include "RenderActions.hpp"

#include <iostream>
#include "rlgl.h"

render::RenderEngine::RenderEngine() : _running(false), _renderDataHandler(), _window(nullptr), _scene(nullptr)
{}

void render::RenderEngine::init()
{
    // Disable Raylib logs
    SetTraceLogLevel(LOG_WARNING);

    this->_window = std::make_unique<RenderWindow>(DEFAULT_WIDTH, DEFAULT_HEIGHT, DEFAULT_TITLE, DEFAULT_FPS);

    this->_scene = std::make_unique<Scene>();
    this->_scene->init();

    this->_running = true;
    GLFWwindow* glfwWindow = static_cast<GLFWwindow*>(GetWindowHandle());
    this->_uiEngine.init(glfwWindow);
}

unsigned int render::RenderEngine::loadTextureFromPixels(unsigned char* pixels, int width, int height)
{
    if (pixels == nullptr || width <= 0 || height <= 0) return 0;

    unsigned int id = rlLoadTexture(pixels, width, height, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8, 1);

    if (id > 0) {
        rlTextureParameters(id, RL_TEXTURE_MAG_FILTER, TEXTURE_FILTER_BILINEAR);
        rlTextureParameters(id, RL_TEXTURE_MIN_FILTER, TEXTURE_FILTER_BILINEAR);
    }

    Texture2D tex = {
        .id = id,
        .width = width,
        .height = height,
        .mipmaps = 1,
        .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8
    };

    this->_textures[id] = tex;
    std::cout << "[Renderer] Font Texture Loaded: ID=" << id << " (" << width << "x" << height << ")" << std::endl;
    
    return id;
}

void render::RenderEngine::setVertexBuffer(common::RenderDataBuffer& buffer)
{
    this->_currentBuffer = buffer;
    this->_renderDataHandler.update(buffer);
}

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
    if (this->_window->ShouldClose()) {
        this->_running = false;
    }

    //! to remove when inputs will be handle in "Inputs" module
    std::queue<common::Action> actions = {};
    inputs::InputHandler::updateActions(actions);
    this->handleActions(actions);

    if (this->_scene) {
        this->_scene->update();
    }
}

void render::RenderEngine::render()
{
    if (!this->_running || !this->_window || !this->_scene)
        return;

    this->_window->BeginDrawing();
    this->_window->ClearBackground();

    this->_scene->render();

    EndMode3D();


    this->_window->DrawFPS();

    // this->_renderDataHandler.render(this->_currentBuffer);
    
    this->_uiEngine.render();

    this->_window->EndDrawing();
}
