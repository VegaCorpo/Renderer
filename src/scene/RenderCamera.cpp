#include "RenderCamera.hpp"

render::RenderCamera::RenderCamera() : _camera()
{}

void render::RenderCamera::init()
{
    this->_camera.position = {10.0f, 10.0f, 10.0f}; // Camera position
    this->_camera.target = {0.0f, 0.0f, 0.0f}; // Look at point
    this->_camera.up = {0.0f, 1.0f, 0.0f}; // Up vector
    this->_camera.fovy = 45.0f; // Field of view
    this->_camera.projection = CAMERA_PERSPECTIVE; // Camera projection type
}

void render::RenderCamera::update()
{
    this->_camera.Update(CAMERA_ORBITAL);
}
