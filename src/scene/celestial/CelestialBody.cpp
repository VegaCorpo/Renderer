#include "CelestialBody.hpp"
#include <raymath.h>

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

void render::CelestialBody::setRealPositionKm(const render::Vector3& position)
{
    if (this->_realPositionKm.x == position.x && this->_realPositionKm.y == position.y &&
        this->_realPositionKm.z == position.z) {
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
    this->_scenePosition = {this->_realPositionKm.x * scaleFactor, this->_realPositionKm.y * scaleFactor,
                            this->_realPositionKm.z * scaleFactor};
}

void render::CelestialBody::computeRenderScale(float sizeScaleFactor)
{
    this->_renderScale = this->_realRadiusKm * sizeScaleFactor;
}

void render::CelestialBody::draw(const std::shared_ptr<ARenderer>& renderer, MeshHandle baseMesh) const
{
    {
        if (!this->_modelInfo || baseMesh == INVALID_MESH) {
            return;
        }

        renderer->drawMesh(baseMesh, this->_modelInfo->texture, this->_scenePosition, this->_renderScale);
    }
}
