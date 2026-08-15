#pragma once

#include <cmath>

namespace render {
    struct Vector3 {
            float x = 0.0f;
            float y = 0.0f;
            float z = 0.0f;

            constexpr Vector3() = default;
            constexpr Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

            [[nodiscard]] float length() const { return std::sqrt(x * x + y * y + z * z); }
            [[nodiscard]] Vector3 normalized() const;

            Vector3& clamp(const Vector3& min, const Vector3& max);
            static Vector3 clamp(const Vector3& v, const Vector3& min, const Vector3& max);

            static Vector3 cross(const Vector3& a, const Vector3& b);
            static float dot(const Vector3& a, const Vector3& b);

            Vector3 operator+(const Vector3& other) const;
            Vector3& operator+=(const Vector3& other);
            Vector3 operator-(const Vector3& other) const;
            Vector3& operator-=(const Vector3& other);
            Vector3 operator*(float scalar) const;
            friend Vector3 operator*(float scalar, const Vector3& vec);
            Vector3& operator*=(float scalar);

            Vector3 operator-() const;

            bool operator==(const Vector3& other) const;
            bool operator!=(const Vector3& other) const;
    };
} // namespace render

#include "Vector3.inl"
