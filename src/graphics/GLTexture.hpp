#pragma once

#include <string>
#include "RenderTypes.hpp"

namespace render {
    struct TextureData {
            unsigned int glId = 0;
            int width = 0;
            int height = 0;
            Color dominantColor = Color::White();
    };

    namespace GLTexture {
        [[nodiscard]] bool load(const std::string& filepath, TextureData& outTexture);
        void destroy(TextureData& texture);
    } // namespace GLTexture
} // namespace render
