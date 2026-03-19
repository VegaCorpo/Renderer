#include "VisualScaleMode.hpp"
#include <algorithm>
#include <cmath>
#include <raymath.h>

render::VisualScaleMode::VisualScaleMode(const VisualScaleConfig& c) : _config(c)
{}

void render::VisualScaleMode::rescale(std::unordered_map<entt::entity, CelestialBody>& bodies)
{
    if (bodies.empty())
        return;

    float maxRadius = 0.0f;
    float maxDistance = 0.0f;

    for (const auto& [_, body] : bodies) {
        maxRadius = std::max(maxRadius, body.getRealRadiusKm());

        float dist = Vector3Length(body.getRealPositionKm());
        maxDistance = std::max(maxDistance, dist);
    }

    for (auto& [_, body] : bodies) {
        float visualScale = 0.0f;

        switch (_config.sizeAlgo) {
            case SizeAlgo::LOG:
            default:
                visualScale = _logSizeScale(body.getRealRadiusKm(), maxRadius);
                break;
        }

        body.setRenderScale(visualScale);
    }

    for (auto& [_, body] : bodies) {
        Vector3 visualPos = {};

        switch (_config.positionAlgo) {
            case PositionAlgo::LOG:
            default:
                visualPos = _logPositionScale(body.getRealPositionKm(), maxDistance);
                break;
        }

        body.setScenePosition(visualPos);
    }

    for (auto& [_, bodyA] : bodies) {
        for (auto& [_, bodyB] : bodies) {

            if (&bodyA == &bodyB)
                continue;

            float dist = Vector3Distance(bodyA.getScenePosition(), bodyB.getScenePosition());
            float minDist = bodyA.getRenderScale() + bodyB.getRenderScale();

            if (dist < minDist && dist > 0.0f) {

                Vector3 dir = Vector3Normalize(Vector3Subtract(bodyB.getScenePosition(), bodyA.getScenePosition()));

                Vector3 corrected = Vector3Add(bodyA.getScenePosition(), Vector3Scale(dir, minDist));

                bodyB.setScenePosition(corrected);
            }
        }
    }
}

float render::VisualScaleMode::_logSizeScale(float realRadius, float maxRadius) const
{
    if (maxRadius <= 0.0f)
        return _config.minVisualRadius;

    const float k = _config.logBoostFactor;
    const float normalized = realRadius / maxRadius;

    const float logScale = std::log(1.0f + std::log(1.0f + normalized * k)) / std::log(1.0f + std::log(1.0f + k));

    const float visual = logScale * _config.maxVisualRadius;

    return std::max(visual, _config.minVisualRadius);
}

Vector3 render::VisualScaleMode::_logPositionScale(const Vector3& realPos, float maxDistance) const
{
    if (maxDistance <= 0.0f)
        return {0, 0, 0};

    const float magnitude = Vector3Length(realPos);

    if (magnitude <= 0.0f)
        return {0, 0, 0};

    const float k = _config.logBoostFactor;

    const float normalized = magnitude / maxDistance;

    const float logScale = std::log(1.0f + normalized * k) / std::log(1.0f + k);

    const float visualMag = logScale * _config.maxVisualDistance;

    return Vector3Scale(Vector3Normalize(realPos), visualMag);
}
