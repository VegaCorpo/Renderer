#pragma once

#include <cstdint>
#include <Eigen/Dense>
#include <string>

namespace render {
    constexpr const char* DEFAULT_TITLE = "Orbital Engine";
    constexpr int DEFAULT_WIDTH = 1280;
    constexpr int DEFAULT_HEIGHT = 800;
    constexpr int DEFAULT_FPS = 60;

    struct RendererConfig {
            int width = DEFAULT_WIDTH;
            int height = DEFAULT_HEIGHT;
            std::string title = DEFAULT_TITLE;
            int fps = DEFAULT_FPS;
    };

    struct CameraView {
            Eigen::Vector3f position{Eigen::Vector3f::Zero()};
            Eigen::Vector3f target{Eigen::Vector3f::Zero()};
            Eigen::Vector3f up{Eigen::Vector3f::UnitY()};
            float fovy = 45.0f;
    };

    using TextureHandle = uint64_t;
    using MeshHandle = uint64_t;

    constexpr TextureHandle INVALID_TEXTURE = 0;
    constexpr MeshHandle INVALID_MESH = 0;

    struct Color {
            unsigned char r, g, b, a;

            // Returns red value as float between 0 and 1
            [[nodiscard]] float r_f() const { return static_cast<float>(r) / 255.0f; }
            // Returns green value as float between 0 and 1
            [[nodiscard]] float g_f() const { return static_cast<float>(g) / 255.0f; }
            // Returns blue value as float between 0 and 1
            [[nodiscard]] float b_f() const { return static_cast<float>(b) / 255.0f; }
            // Returns alpha value as float between 0 and 1
            [[nodiscard]] float a_f() const { return static_cast<float>(a) / 255.0f; }

            static Color White() { return {255, 255, 255, 255}; }
            static Color Black() { return {0, 0, 0, 255}; }
    };
} // namespace render
