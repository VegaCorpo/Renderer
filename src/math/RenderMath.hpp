#pragma once

#include "RenderTypes.hpp"

namespace render {
    constexpr float PI = 3.14159265358979323846f;
    constexpr float DEG2RAD = PI / 180.0f;
    constexpr float RAD2DEG = 180.0f / PI;

    struct Vector2 {
            float x = 0.0f;
            float y = 0.0f;

            Vector2 operator+(const Vector2& other) const { return {x + other.x, y + other.y}; }
            Vector2 operator*(float scalar) const { return {x * scalar, y * scalar}; }
            [[nodiscard]] float length() const { return std::sqrt(x * x + y * y); }
    };

    struct Matrix4 {
            float m[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};

            static Matrix4 lookAt(const Vector3& eye, const Vector3& target, const Vector3& up)
            {
                Vector3 f = (target - eye).normalized();
                Vector3 s = Vector3::cross(f, up).normalized();
                Vector3 u = Vector3::cross(s, f);

                Matrix4 result;
                result.m[0] = s.x;
                result.m[4] = s.y;
                result.m[8] = s.z;
                result.m[12] = -Vector3::dot(s, eye);
                result.m[1] = u.x;
                result.m[5] = u.y;
                result.m[9] = u.z;
                result.m[13] = -Vector3::dot(u, eye);
                result.m[2] = -f.x;
                result.m[6] = -f.y;
                result.m[10] = -f.z;
                result.m[14] = Vector3::dot(f, eye);
                result.m[3] = 0.0f;
                result.m[7] = 0.0f;
                result.m[11] = 0.0f;
                result.m[15] = 1.0f;
                return result;
            }

            static Matrix4 perspective(float fovyRad, float aspect, float nearPlane, float farPlane)
            {
                float tanHalfFovy = std::tan(fovyRad / 2.0f);
                Matrix4 result = {};
                result.m[0] = 1.0f / (aspect * tanHalfFovy);
                result.m[5] = 1.0f / (tanHalfFovy);
                result.m[10] = -(farPlane + nearPlane) / (farPlane - nearPlane);
                result.m[11] = -1.0f;
                result.m[14] = -(2.0f * farPlane * nearPlane) / (farPlane - nearPlane);
                return result;
            }

            static Vector3 rotateY(const Vector3& v, float angleRad)
            {
                float cosA = std::cos(angleRad);
                float sinA = std::sin(angleRad);
                return {v.x * cosA + v.z * sinA, v.y, -v.x * sinA + v.z * cosA};
            }

            static Vector3 rotateAxis(const Vector3& v, const Vector3& axis, float angleRad)
            {
                float cosA = std::cos(angleRad);
                float sinA = std::sin(angleRad);
                Vector3 u = axis.normalized();

                return v * cosA + Vector3::cross(u, v) * sinA + u * Vector3::dot(u, v) * (1.0f - cosA);
            }

            static Vector2 GetWorldToScreen(const Vector3& position, const CameraView& camera, float screenWidth,
                                            float screenHeight)
            {
                Matrix4 view = Matrix4::lookAt(camera.position, camera.target, camera.up);

                float aspect = screenWidth / screenHeight;
                float fovyRad = camera.fovy * DEG2RAD;
                Matrix4 proj = Matrix4::perspective(fovyRad, aspect, 0.1f, 10000.0f);

                Vector3 v = position - camera.position;

                Vector3 viewPos = {view.m[0] * v.x + view.m[4] * v.y + view.m[8] * v.z,
                                   view.m[1] * v.x + view.m[5] * v.y + view.m[9] * v.z,
                                   view.m[2] * v.x + view.m[6] * v.y + view.m[10] * v.z};

                if (viewPos.z >= 0.0f) {
                    return {-1000.0f, -1000.0f};
                }

                float tanHalfFovy = std::tan(fovyRad / 2.0f);

                float ndcX = (viewPos.x / (aspect * tanHalfFovy)) / -viewPos.z;
                float ndcY = (viewPos.y / tanHalfFovy) / -viewPos.z;

                float screenX = (ndcX + 1.0f) * 0.5f * screenWidth;
                float screenY = (1.0f - ndcY) * 0.5f * screenHeight;

                return {screenX, screenY};
            }
    };
} // namespace render
