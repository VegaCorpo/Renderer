#include "RenderCamera.hpp"
#include <raylib.h>
#include <raymath.h>

render::RenderCamera::RenderCamera() : _camera(), _movementDir(0, 0, 0), _rotationDir(0, 0)
{}

void render::RenderCamera::init()
{
    this->_camera.position = {1.5f, .2f, .5f}; // Camera position
    this->_camera.target = {.0f, .0f, .0f}; // Look at point
    this->_camera.up = {0.0f, 1.0f, 0.0f}; // Up vector
    this->_camera.fovy = 45.0f; // Field of view
    this->_camera.projection = CAMERA_PERSPECTIVE; // Camera projection type
}

void render::RenderCamera::addMovement(Vector3 dir)
{
    _movementDir = Vector3Add(_movementDir, dir);
    _movementDir = Vector3Clamp(_movementDir, {-1, -1, -1}, {1, 1, 1});
}

void render::RenderCamera::addRotation(Vector2 rot)
{
    _rotationDir = Vector2Add(_rotationDir, rot);
    _rotationDir = Vector2Clamp(_rotationDir, {-1, -1}, {1, 1});
}

void render::RenderCamera::update()
{
    this->_move();
    this->_rotate();
}

void render::RenderCamera::_move()
{
    if (Vector3Length(_movementDir) == 0.0001f)
        return;

    Vector3 forward = Vector3Normalize(Vector3Subtract(_camera.target, _camera.position));
    Vector3 right = Vector3Normalize(Vector3CrossProduct(forward, _camera.up));
    Vector3 up = _camera.up;

    Vector3 moveWorld = {forward.x * _movementDir.z + right.x * _movementDir.x + up.x * _movementDir.y,
                         forward.y * _movementDir.z + right.y * _movementDir.x + up.y * _movementDir.y,
                         forward.z * _movementDir.z + right.z * _movementDir.x + up.z * _movementDir.y};

    moveWorld = Vector3Scale(moveWorld, MOVE_SPEED);

    _camera.position = Vector3Add(_camera.position, moveWorld);
    _camera.target = Vector3Add(_camera.target, moveWorld);
}

void render::RenderCamera::_rotate()
{
    if (Vector2Length(_rotationDir) <= 0.0001f)
        return;

    Vector3 forward = Vector3Normalize(Vector3Subtract(_camera.target, _camera.position));

    Matrix yawMat = MatrixRotateY(-_rotationDir.x * ROTATION_SPEED);
    forward = Vector3Transform(forward, yawMat);

    Vector3 right = Vector3Normalize(Vector3CrossProduct(forward, _camera.up));
    Matrix pitchMat = MatrixRotate(right, -_rotationDir.y * ROTATION_SPEED);
    forward = Vector3Transform(forward, pitchMat);

    _camera.target = Vector3Add(_camera.position, forward);
}
