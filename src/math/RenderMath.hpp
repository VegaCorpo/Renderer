#pragma once

#include <Eigen/Dense>
#include <Eigen/Geometry>

namespace render::math {
    inline Eigen::Vector3f clamp(const Eigen::Vector3f& v, const Eigen::Vector3f& minVal, const Eigen::Vector3f& maxVal)
    {
        return v.cwiseMax(minVal).cwiseMin(maxVal);
    }

    inline Eigen::Vector3f clamp(const Eigen::Vector3f& v, float minVal, float maxVal)
    {
        return v.cwiseMax(minVal).cwiseMin(maxVal);
    }

    inline Eigen::Vector3f rotateAxis(const Eigen::Vector3f& vec, const Eigen::Vector3f& axis, float angleRad)
    {
        return Eigen::AngleAxisf(angleRad, axis.normalized()) * vec;
    }

    inline Eigen::Vector3f rotateY(const Eigen::Vector3f& vec, float angleRad)
    {
        return Eigen::AngleAxisf(angleRad, Eigen::Vector3f::UnitY()) * vec;
    }
} // namespace render::math
