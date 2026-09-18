#include "RenderCamera.hpp"
#include "RenderMath.hpp"

render::RenderCamera::RenderCamera() :
    _cameraView(), _movementDir(Eigen::Vector3f::Zero()), _rotationDir(Eigen::Vector3f::Zero()), _isFollowing(false),
    _followedEntity()
{}

void render::RenderCamera::init()
{
    this->_cameraView.position = {-30.0f, 10.0f, 15.0f}; // Camera position
    this->_cameraView.target = {0.0f, 0.0f, 0.0f}; // Look at point
    this->_cameraView.up = {0.0f, 1.0f, 0.0f}; // Up vector
    this->_cameraView.fovy = 45.0f; // Field of view
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

void render::RenderCamera::follow(entt::entity entity)
{
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

void render::RenderCamera::_rotate()
{
    if (_rotationDir.squaredNorm() <= 0.000001f)
        return;

    Eigen::Vector3f forward = (_cameraView.target - _cameraView.position).normalized();

    if (std::abs(_rotationDir.x()) > 0.0001f) {
        forward = render::math::rotateY(forward, -_rotationDir.x() * ROTATION_SPEED);
    }

    if (std::abs(_rotationDir.y()) > 0.0001f) {
        Eigen::Vector3f right = forward.cross(_cameraView.up).normalized();
        forward = render::math::rotateAxis(forward, right, -_rotationDir.y() * ROTATION_SPEED);
    }

    if (std::abs(_rotationDir.z()) > 0.0001f) {
        _cameraView.up = render::math::rotateAxis(_cameraView.up, forward, _rotationDir.z() * ROTATION_SPEED);
    }

    _cameraView.target = _cameraView.position + forward;
}
