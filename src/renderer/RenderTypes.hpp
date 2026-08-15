#pragma once

#include <cstdint>
#include <string>
#include "Vector3.hpp"

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
            Vector3 position{};
            Vector3 target{};
            Vector3 up{};
            float fovy = 0;
    };

    using TextureHandle = uint64_t;
    using MeshHandle = uint64_t;

    constexpr TextureHandle INVALID_TEXTURE = 0;
    constexpr MeshHandle INVALID_MESH = 0;

    struct Color {
            unsigned char r, g, b, a;

            static Color White() { return {255, 255, 255, 255}; }
            static Color Black() { return {0, 0, 0, 255}; }
    };
} // namespace render
