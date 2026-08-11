#include "RenderCamera.hpp"
#include "RenderMath.hpp"

render::RenderCamera::RenderCamera() :
    _cameraView(), _movementDir(), _rotationDir(), _isFollowing(false), _followedEntity()
{}

void render::RenderCamera::init()
{
    this->_cameraView.position = {150.f, 20.f, 50.f}; // Camera position
    this->_cameraView.target = {.0f, .0f, .0f}; // Look at point
    this->_cameraView.up = {0.0f, 1.0f, 0.0f}; // Up vector
    this->_cameraView.fovy = 45.0f; // Field of view
}

void render::RenderCamera::addMovement(Vector3 dir)
{
    _movementDir += dir;
    _movementDir.clamp({-1, -1, -1}, {1, 1, 1});
}

void render::RenderCamera::addRotation(Vector3 rot)
{
    _rotationDir += rot;
    _rotationDir.clamp({-1, -1, -1}, {1, 1, 1});
}

void render::RenderCamera::update()
{
    this->_move();
    this->_rotate();
}

void render::RenderCamera::follow(entt::entity entity)
{
    this->_isFollowing = true;
    this->_followedEntity = entity;
}

void render::RenderCamera::_move()
{
    if (_movementDir.length() <= 0.0001f)
        return;

    Vector3 forward = (_cameraView.target - _cameraView.position).normalized();
    Vector3 right = Vector3::cross(forward, _cameraView.up).normalized();
    Vector3 up = _cameraView.up;

    Vector3 moveWorld = forward * _movementDir.z + right * _movementDir.x + up * _movementDir.y;

    moveWorld *= MOVE_SPEED;
    _cameraView.position += moveWorld;
    _cameraView.target += moveWorld;
}

void render::RenderCamera::_rotate()
{
    if (_rotationDir.length() <= 0.0001f)
        return;

    Vector3 forward = (_cameraView.target - _cameraView.position).normalized();

    if (std::abs(_rotationDir.x) > 0.0001f) {
        forward = Matrix4::rotateY(forward, -_rotationDir.x * ROTATION_SPEED);
    }

    if (std::abs(_rotationDir.y) > 0.0001f) {
        Vector3 right = Vector3::cross(forward, _cameraView.up).normalized();
        forward = Matrix4::rotateAxis(forward, right, -_rotationDir.y * ROTATION_SPEED);
    }

    if (std::abs(_rotationDir.z) > 0.0001f) {
        _cameraView.up = Matrix4::rotateAxis(_cameraView.up, forward, _rotationDir.z * ROTATION_SPEED);
    }

    _cameraView.target = _cameraView.position + forward;
}
