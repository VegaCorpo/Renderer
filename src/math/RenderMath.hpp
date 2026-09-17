#pragma once

#include <Eigen/Dense>

namespace render::math {
    inline Eigen::Vector3f clamp(const Eigen::Vector3f& vector, const Eigen::Vector3f& minVal,
                                 const Eigen::Vector3f& maxVal)
    {
        return vector.cwiseMax(minVal).cwiseMin(maxVal);
    }

    inline Eigen::Vector3f clamp(const Eigen::Vector3f& vector, float minVal, float maxVal)
    {
        return vector.cwiseMax(minVal).cwiseMin(maxVal);
    }

    inline Eigen::Vector3f rotateAxis(const Eigen::Vector3f& vector, const Eigen::Vector3f& axis, float angleRad)
    {
        return Eigen::AngleAxisf(angleRad, axis.normalized()) * vector;
    }

    inline Eigen::Vector3f rotateY(const Eigen::Vector3f& vector, float angleRad)
    {
        return Eigen::AngleAxisf(angleRad, Eigen::Vector3f::UnitY()) * vector;
    }
} // namespace render::math
