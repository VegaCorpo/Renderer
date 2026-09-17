#include "CelestialBody.hpp"

render::CelestialBody::CelestialBody() :
    _hasBeenInitialized(false), _hasBeenModified(true), _name(), _realPositionKm(), _scenePosition(),
    _realRadiusKm(0.0f), _renderScale(0.0f), _modelInfo(nullptr)
{}

bool render::CelestialBody::hasBeenModified()
{
    if (!this->_hasBeenModified) {
        return false;
    }

    this->_hasBeenModified = false;
    return true;
}

void render::CelestialBody::setRealPositionKm(const Eigen::Vector3f& position)
{
    if (this->_realPositionKm.x() == position.x() && this->_realPositionKm.y() == position.y() &&
        this->_realPositionKm.z() == position.z()) {
        return;
    }

    this->_realPositionKm = position;
    this->modified();
}

void render::CelestialBody::setRealRadiusKm(float radius)
{
    if (this->_realRadiusKm != radius) {
        this->modified();
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
    this->_scenePosition = this->_realPositionKm * scaleFactor;
}

void render::CelestialBody::computeRenderScale(float sizeScaleFactor)
{
    this->_renderScale = this->_realRadiusKm * sizeScaleFactor;
}

void render::CelestialBody::draw(GLRenderer& renderer) const
{
    if (!this->_drawable) {
        return;
    }

    this->_drawable->draw(renderer, {this->_scenePosition, this->_renderScale});
}
