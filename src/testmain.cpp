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

#include "raylib-cpp.hpp"
#include <iostream>

int main()
{
    // Init window
    raylib::Window window(1280, 720, "Raylib Model Test");
    SetTargetFPS(60);

    SetTraceLogLevel(LOG_WARNING);

    // Simple camera
    raylib::Camera3D camera(
        raylib::Vector3(5.0f, 3.0f, 5.0f),   // position
        raylib::Vector3(0.0f, 0.0f, 0.0f),   // target
        raylib::Vector3(0.0f, 1.0f, 0.0f),   // up
        45.0f,                               // fov
        CAMERA_PERSPECTIVE
    );

    // 1) Charger le modèle complet depuis l'OBJ
    raylib::Model tempModel("../assets/models/UVSphere.obj");

    // 2) Extraire le mesh et l'uploader seul
    raylib::Mesh sphereMesh = tempModel.meshes[0];

    // 3) Créer un nouveau modèle propre depuis le mesh
    raylib::Texture textureEarth("../assets/textures/earth.jpg");

    raylib::Model earthModel = LoadModelFromMesh(sphereMesh);
    earthModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = textureEarth;

    // sphereModel.transform = MatrixTranslate(0.0f, 0.0f, 0.0f);

    // raylib::Model modelGlb("../assets/models/Venus.glb");   // textures intégrées, recommandé

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
