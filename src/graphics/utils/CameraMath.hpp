#pragma once

#include <cmath>
#include <Eigen/Dense>
#include <Eigen/Geometry>
#include "RenderTypes.hpp"

namespace render::math {
    // Pure camera maths: build the expected view/projection matrices
    // for OpenGL using the CameraView structure from the scene.

    inline Eigen::Matrix4f buildView(const CameraView& camera)
    {
        Eigen::Vector3f forward = (camera.target - camera.position).normalized();
        Eigen::Vector3f right = forward.cross(camera.up).normalized();
        Eigen::Vector3f up = right.cross(forward);

        Eigen::Matrix4f view = Eigen::Matrix4f::Identity();
        view(0, 0) = right.x();
        view(0, 1) = right.y();
        view(0, 2) = right.z();
        view(1, 0) = up.x();
        view(1, 1) = up.y();
        view(1, 2) = up.z();
        view(2, 0) = -forward.x();
        view(2, 1) = -forward.y();
        view(2, 2) = -forward.z();

        view(0, 3) = -right.dot(camera.position);
        view(1, 3) = -up.dot(camera.position);
        view(2, 3) = forward.dot(camera.position);

        return view;
    }

    inline Eigen::Matrix4f buildProjection(float fovyDegrees, float aspect, float nearPlane, float farPlane)
    {
        const float fovyRad = fovyDegrees * static_cast<float>(EIGEN_PI) / 180.0f;
        const float f = 1.0f / std::tan(fovyRad / 2.0f);

        Eigen::Matrix4f proj = Eigen::Matrix4f::Zero();
        proj(0, 0) = f / aspect;
        proj(1, 1) = f;
        proj(2, 2) = (farPlane + nearPlane) / (nearPlane - farPlane);
        proj(2, 3) = (2.0f * farPlane * nearPlane) / (nearPlane - farPlane);
        proj(3, 2) = -1.0f;

        return proj;
    }
} // namespace render::math
