#include "GLTexture.hpp"
#include <glad/gl.h>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

bool render::GLTexture::load(const std::string& filepath, TextureData& outTexture)
{
    int channels = 0;
    unsigned char* pixels = stbi_load(filepath.c_str(), &outTexture.width, &outTexture.height, &channels, 4);

    if (!pixels) {
        std::cerr << "[GLTexture] cannot load " << filepath << "\n";
        return false;
    }

    long r = 0, g = 0, b = 0;
    const long count = static_cast<long>(outTexture.width) * outTexture.height;
    for (long i = 0; i < count; ++i) {
        r += pixels[i * 4 + 0];
        g += pixels[i * 4 + 1];
        b += pixels[i * 4 + 2];
    }
    outTexture.dominantColor = Color{
        static_cast<unsigned char>(r / count),
        static_cast<unsigned char>(g / count),
        static_cast<unsigned char>(b / count),
        255,
    };

    glGenTextures(1, &outTexture.glId);
    glBindTexture(GL_TEXTURE_2D, outTexture.glId);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, outTexture.width, outTexture.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(pixels);
    return true;
}

void render::GLTexture::destroy(TextureData& texture)
{
    if (texture.glId != 0) {
        glDeleteTextures(1, &texture.glId);
        texture.glId = 0;
    }
}
