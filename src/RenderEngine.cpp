#include "RenderEngine.hpp"

#include <iostream>
#include "rlgl.h"

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

unsigned int render::RenderEngine::loadTextureFromPixels(unsigned char* pixels, int width, int height)
{
    if (pixels == nullptr || width <= 0 || height <= 0) return 0;

    // 1. Charger la texture via rlgl directement pour éviter les surcouches
    unsigned int id = rlLoadTexture(pixels, width, height, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8, 1);

    if (id > 0) {
        rlTextureParameters(id, RL_TEXTURE_MAG_FILTER, TEXTURE_FILTER_BILINEAR);
        rlTextureParameters(id, RL_TEXTURE_MIN_FILTER, TEXTURE_FILTER_BILINEAR);
    }

    // 2. On crée l'objet Texture2D pour Raylib
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

void render::RenderEngine::update(entt::registry& registry)
{
    if (this->_window->ShouldClose()) {
        this->_running = false;
    }

    if (this->_scene) {
        this->_scene->update(registry);
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

    this->_renderDataHandler.render(this->_currentBuffer);

    if (!this->_textures.empty()) {
        auto& tex = this->_textures.begin()->second;
        DrawTexture(tex, 900, 0, WHITE);
    }

    this->_window->EndDrawing();
}
