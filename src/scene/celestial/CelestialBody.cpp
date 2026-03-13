#include "CelestialBody.hpp"
#include <raymath.h>

render::CelestialBody::CelestialBody() :
    _name(), _realPositionKm(0.0f), _scenePosition(0.0f), _realRadiusKm(0.0f), _renderScale(0.0f), _model(nullptr),
    _color(WHITE), _hasBeenModified(true)
{}

bool render::CelestialBody::hasBeenModified()
{
    if (!this->_hasBeenModified) {
        return false;
    }

    this->_hasBeenModified = false;
    return true;
}

void render::CelestialBody::setRealPositionKm(const Vector3& position)
{
    if (!Vector3Equals(this->_realPositionKm, position)) {
        this->_modified();
    }

    this->_realPositionKm = position;
}

void render::CelestialBody::setRealRadiusKm(float radius)
{
    if (this->_realRadiusKm != radius) {
        this->_modified();
    }

    this->_realRadiusKm = radius;
}

void render::CelestialBody::computePositionAndScale(float scaleFactor)
{
    this->computeScenePosition(scaleFactor);
    this->computeRenderScale(scaleFactor);
}

void render::CelestialBody::computeScenePosition(float scaleFactor)
{
    this->_scenePosition = Vector3Scale(_realPositionKm, scaleFactor);
}

void render::CelestialBody::computeRenderScale(float sizeScaleFactor)
{
    this->_renderScale = this->_realRadiusKm * sizeScaleFactor;
}

void render::CelestialBody::render() const
{
    if (!this->_model) {
        return;
    }

    this->_model->Draw(this->_scenePosition, this->_renderScale, this->_color);
}
