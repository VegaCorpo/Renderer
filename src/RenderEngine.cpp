#include "RenderEngine.hpp"

render::RenderEngine::RenderEngine() :
    _running(false), _width(0), _height(0), _fps(60), _title("Raylib - The next generation")
{}

render::RenderEngine::~RenderEngine()
{
    if (this->_running) {
        CloseWindow();
    }
}

void render::RenderEngine::init()
{
    if (this->_width <= 0)
        this->_width = GetScreenWidth();
    if (this->_height <= 0)
        this->_height = GetScreenHeight();

    // Disable Raylib logs
    SetTraceLogLevel(LOG_NONE);

    SetConfigFlags(FLAG_FULLSCREEN_MODE);
    InitWindow(this->_width, this->_height, this->_title);
    SetTargetFPS(this->_fps);

    // Setup camera 3D
    this->_camera.position = {4.0f, 4.0f, 4.0f}; // Camera position
    this->_camera.target = {0.0f, 0.0f, 0.0f}; // Look at point
    this->_camera.up = {0.0f, 1.0f, 0.0f}; // Up vector
    this->_camera.fovy = 45.0f; // Field of view
    this->_camera.projection = CAMERA_PERSPECTIVE; // Camera projection type

    this->_running = true;
}

void render::RenderEngine::setUIBuffer() {}

void render::RenderEngine::update()
{
    if (WindowShouldClose()) {
        this->_running = false;
    }

    this->render();
}

void render::RenderEngine::render()
{
    if (!this->_running)
        return;

    BeginDrawing();
    ClearBackground(RAYWHITE);

    BeginMode3D(this->_camera);

    DrawSphere({0, 0, 0}, 1.0f, RED);
    DrawGrid(10, 1.0f);

    EndMode3D();

    DrawFPS(10, 10);

    EndDrawing();
}
