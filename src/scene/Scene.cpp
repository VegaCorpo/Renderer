#include "Scene.hpp"
#include <Mesh.hpp>
#include <raylib.h>

render::Scene::Scene() : _camera(nullptr)
{}

void render::Scene::init()
{
    this->_camera = std::make_unique<RenderCamera>();
    this->_camera->init();

    this->_sphere = std::make_unique<raylib::Model>(raylib::Mesh::Sphere(1.0f, 32, 32));
    this->_plane = std::make_unique<raylib::Model>(raylib::Mesh::Plane(10.f, 10.f, 5, 5));
}

void render::Scene::update()
{
    if (this->_camera)
        this->_camera->update();
}

void render::Scene::render()
{
    this->_sphere->Draw({0, 0, 0}, 1.0f, RED);
    this->_plane->Draw({0, 0, 0}, 0.2f, BLUE);
    this->_plane->Draw({0, -1, 0}, 1.0f, WHITE);
}
