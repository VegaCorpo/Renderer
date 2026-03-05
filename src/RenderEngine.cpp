#include "RenderEngine.hpp"
#include <MeshUnmanaged.hpp>
#include <memory>
#include <raylib.h>

render::RenderEngine::RenderEngine() :
    _running(false), _width(0), _height(0), _fps(60), _window(nullptr)
{}

void render::RenderEngine::init()
{
    if (this->_width <= 0)
        this->_width = GetScreenWidth();
    if (this->_height <= 0)
        this->_height = GetScreenHeight();

    // Disable Raylib logs
    SetTraceLogLevel(LOG_NONE);

    this->_window = std::make_unique<raylib::Window>(this->_width, this->_height, DEFAULT_TITLE, FLAG_FULLSCREEN_MODE);
    this->_window->SetTargetFPS(this->_fps);

    // Setup camera 3D
    this->_camera.position = {10.0f, 10.0f, 10.0f}; // Camera position
    this->_camera.target = {0.0f, 0.0f, 0.0f}; // Look at point
    this->_camera.up = {0.0f, 1.0f, 0.0f}; // Up vector
    this->_camera.fovy = 45.0f; // Field of view
    this->_camera.projection = CAMERA_PERSPECTIVE; // Camera projection type

    this->_running = true;

    this->_sphere = std::make_unique<raylib::Model>(raylib::Mesh::Sphere(1.0f, 32, 32));
    this->_plane = std::make_unique<raylib::Model>(raylib::Mesh::Plane(10.f, 10.f, 5, 5));
}

void render::RenderEngine::setVertexBuffer(/* std::vector<Vertex> vertexBuffer */) {}

void render::RenderEngine::update()
{
    if (this->_window->ShouldClose()) {
        this->_running = false;
    }

    this->_camera.Update(CAMERA_ORBITAL);
    this->render();
}

void render::RenderEngine::render()
{
    if (!this->_running)
        return;

    this->_window->BeginDrawing();
    this->_window->ClearBackground(DARKBLUE);

    BeginMode3D(this->_camera);

    this->_sphere->Draw({0,0,0}, 1.0f, RED);
    this->_plane->Draw({0, 0, 0}, 0.2f, BLUE);
    this->_plane->Draw({0, -1, 0}, 1.0f, WHITE);

    EndMode3D();

    this->_window->DrawFPS();

    this->_window->EndDrawing();
}
