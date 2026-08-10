// #include <chrono>
// #include <components/mass.hpp>
// #include <components/position.hpp>
// #include <thread>
// #include "RenderEngine.hpp"

// int main()
// {
//     render::RenderEngine renderer;

//     renderer.init();

//     entt::registry registry;

//     while (renderer.isRunning()) {
//         renderer.syncIn(registry);
//         renderer.update();
//         std::this_thread::sleep_for(std::chrono::milliseconds(16));
//     }
// }

#include <raylib-cpp.hpp>

int main()
{
    // Init window
    raylib::Window window(1280, 720, "Raylib Model Test");
    SetTargetFPS(60);

    SetTraceLogLevel(LOG_WARNING);

    // Simple camera
    raylib::Camera3D camera(
        raylib::Vector3(2.0f, 2.0f, 2.0f),   // position
        raylib::Vector3(0.0f, 0.0f, 0.0f),   // target
        raylib::Vector3(0.0f, 1.0f, 0.0f),   // up
        45.0f,                               // fov
        CAMERA_PERSPECTIVE
    );

    raylib::Model earthModel("../assets/models/UVSphere.obj");

    raylib::Texture textureEarth("../assets/textures/earth.jpg");

    earthModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = textureEarth;

    while (!window.ShouldClose())
    {
        UpdateCamera(&camera, CAMERA_ORBITAL);

        window.BeginDrawing();
        {
            window.ClearBackground(RAYWHITE);

            BeginMode3D(camera);

            earthModel.Draw({0, 0, 0}, 1.0f);

            DrawGrid(20, 1.0f);

            EndMode3D();

            DrawText("Sphere base + Texture Terre", 10, 10, 20, DARKGRAY);
        }
        window.EndDrawing();
    }

    return 0;
}
