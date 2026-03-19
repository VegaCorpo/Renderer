#include "ResourceManager.hpp"
#include <iostream>
#include <utils/assets.hpp>

render::ResourceManager::ResourceManager() : _baseMesh()
{
    this->_baseMesh = raylib::Mesh::Sphere(1, 32, 32);

    this->_modelCache[common::DEFAULT_TEXTURE_PATH] = this->_createModelInfoFromTexture(common::DEFAULT_TEXTURE_PATH);
}

render::ResourceManager::~ResourceManager()
{
    if (_defaultTexture.id != 0) {
        UnloadTexture(_defaultTexture);
    }
}

std::shared_ptr<render::ModelInfo> render::ResourceManager::getOrCreateModelInfo(const std::string& textureId)
{
    auto it = _modelCache.find(textureId);
    if (it != _modelCache.end())
        return it->second;

    auto info = _createModelInfoFromTexture(textureId);
    _modelCache[textureId] = info;

    return info;
}

std::shared_ptr<render::ModelInfo> render::ResourceManager::_createModelInfoFromTexture(const std::string& texturePath)
{
    std::string fullPath = common::TEXTURE_PATH + texturePath;
    Texture2D tex = LoadTexture(fullPath.c_str());

    if (tex.id == 0) {
        std::cerr << "[ResourceManager] Error loading " << fullPath << " — using default texture\n";
        return _modelCache["default.jpg"];
    }

    auto info = std::make_shared<ModelInfo>();

    info->model = raylib::Model(_baseMesh);

    info->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = tex;

    info->dominantColor = _computeDominantColor(tex);

    return info;
}

Color render::ResourceManager::_computeDominantColor(const Texture2D& tex)
{
    Image img = LoadImageFromTexture(tex);
    Color* pixels = LoadImageColors(img);

    long r = 0, g = 0, b = 0;
    const size_t count = img.width * img.height;

    for (size_t i = 0; i < count; i++) {
        r += pixels[i].r;
        g += pixels[i].g;
        b += pixels[i].b;
    }

    UnloadImageColors(pixels);
    UnloadImage(img);

    return Color{static_cast<unsigned char>(r / count), static_cast<unsigned char>(g / count),
                 static_cast<unsigned char>(b / count), 255};
}
