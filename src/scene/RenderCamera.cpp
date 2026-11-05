#include "RenderCamera.hpp"
#include "RenderMath.hpp"

render::RenderCamera::RenderCamera() :
    _cameraView(), _movementDir(Eigen::Vector3f::Zero()), _rotationDir(Eigen::Vector3f::Zero()), _isFollowing(false),
    _followedEntity()
{}

void render::RenderCamera::init()
{
    this->_cameraView.position = {150.0f, 20.0f, 50.0f}; // Camera position
    this->_cameraView.target = {0.0f, 0.0f, 0.0f}; // Look at point
    this->_cameraView.up = {0.0f, 1.0f, 0.0f}; // Up vector
    this->_cameraView.fovy = 45.0f; // Field of view

    this->follow();
}

void render::RenderCamera::addMovement(Eigen::Vector3f dir)
{
    _movementDir += dir;
    _movementDir = render::math::clamp(_movementDir, -1.0f, 1.0f);
}

void render::RenderCamera::addRotation(Eigen::Vector3f rot)
{
    _rotationDir += rot;
    _rotationDir = render::math::clamp(_rotationDir, -1.0f, 1.0f);
}

void render::RenderCamera::update()
{
    this->_move();
    this->_rotate();
}

void render::RenderCamera::follow(std::size_t entity)
{
    if (entity == SIZE_MAX) {
        this->_isFollowing = false;
        this->_followedEntity = SIZE_MAX;
        return;
    }

    this->_isFollowing = true;
    this->_followedEntity = entity;
}

void render::RenderCamera::_move()
{
    if (_movementDir.squaredNorm() <= 0.000001f)
        return;

    Eigen::Vector3f forward = (_cameraView.target - _cameraView.position).normalized();
    Eigen::Vector3f right = forward.cross(_cameraView.up).normalized();
    Eigen::Vector3f up = _cameraView.up;

    Eigen::Vector3f moveWorld = forward * _movementDir.z() + right * _movementDir.x() + up * _movementDir.y();

    moveWorld *= MOVE_SPEED;
    _cameraView.position += moveWorld;
    _cameraView.target += moveWorld;
}

void render::RenderCamera::addMouseRotation(float deltaX, float deltaY)
{
    this->_applyRotation(deltaX * MOUSE_SENSITIVITY, deltaY * MOUSE_SENSITIVITY, 0.0f);
}

void render::RenderCamera::_rotate()
{
    if (_rotationDir.squaredNorm() <= 0.000001f)
        return;

    this->_applyRotation(_rotationDir.x() * ROTATION_SPEED, _rotationDir.y() * ROTATION_SPEED,
                         _rotationDir.z() * ROTATION_SPEED);
}

void render::RenderCamera::_applyRotation(float yaw, float pitch, float roll)
{
    Eigen::Vector3f forward = (_cameraView.target - _cameraView.position).normalized();

    if (std::abs(yaw) > 0.000001f) {
        forward = render::math::rotateY(forward, -yaw);
    }

    if (std::abs(pitch) > 0.000001f) {
        Eigen::Vector3f right = forward.cross(_cameraView.up).normalized();
        forward = render::math::rotateAxis(forward, right, -pitch);
    }

    if (std::abs(roll) > 0.000001f) {
        _cameraView.up = render::math::rotateAxis(_cameraView.up, forward, roll);
    }

    _cameraView.target = _cameraView.position + forward;
}
