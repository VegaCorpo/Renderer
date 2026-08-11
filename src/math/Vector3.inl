#pragma once

#include <algorithm>
#include "Vector3.hpp"

namespace render {
    inline Vector3 Vector3::normalized() const
    {
        float len = length();
        if (len <= 0.00001f)
            return {0.0f, 0.0f, 0.0f};
        return {x / len, y / len, z / len};
    }

    inline Vector3& Vector3::clamp(const Vector3& min, const Vector3& max)
    {
        x = std::clamp(x, min.x, max.x);
        y = std::clamp(y, min.y, max.y);
        z = std::clamp(z, min.z, max.z);
        return *this;
    }

    // Note: Pas de mot-clé 'static' ici !
    inline Vector3 Vector3::clamp(const Vector3& v, const Vector3& min, const Vector3& max)
    {
        return {std::clamp(v.x, min.x, max.x), std::clamp(v.y, min.y, max.y), std::clamp(v.z, min.z, max.z)};
    }

    // Note: Pas de mot-clé 'static' ici !
    inline Vector3 Vector3::cross(const Vector3& a, const Vector3& b)
    {
        return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
    }

    inline float Vector3::dot(const Vector3& a, const Vector3& b)
    {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    inline Vector3 Vector3::operator+(const Vector3& other) const
    {
        return {x + other.x, y + other.y, z + other.z};
    }

    inline Vector3& Vector3::operator+=(const Vector3& other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    inline Vector3 Vector3::operator-(const Vector3& other) const
    {
        return {x - other.x, y - other.y, z - other.z};
    }

    inline Vector3& Vector3::operator-=(const Vector3& other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    inline Vector3 Vector3::operator*(float scalar) const
    {
        return {x * scalar, y * scalar, z * scalar};
    }

    inline Vector3& Vector3::operator*=(float scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }

    inline Vector3 operator*(float scalar, const Vector3& vec)
    {
        return vec * scalar;
    }

    inline Vector3 Vector3::operator-() const
    {
        return {-x, -y, -z};
    }

    inline bool Vector3::operator==(const Vector3& other) const
    {
        constexpr float epsilon = 0.00001f;
        return std::abs(x - other.x) < epsilon && std::abs(y - other.y) < epsilon && std::abs(z - other.z) < epsilon;
    }

    inline bool Vector3::operator!=(const Vector3& other) const
    {
        return !(*this == other);
    }

} // namespace render
