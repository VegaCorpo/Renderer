#include "ResourceManager.hpp"
#include <iostream>
#include <utils/assets.hpp>

render::ResourceManager::ResourceManager() : _baseMesh()
{
    this->_baseMesh = raylib::Mesh::Sphere(1, 32, 32);

    this->_modelCache[common::DEFAULT_TEXTURE_ID] = std::make_shared<raylib::Model>(_baseMesh);
}

render::ResourceManager::~ResourceManager()
{
    if (_defaultTexture.id != 0) {
        UnloadTexture(_defaultTexture);
    }
}

std::shared_ptr<raylib::Model> render::ResourceManager::getOrCreateModel(const std::string& textureId)
{
    auto it = _modelCache.find(textureId);
    if (it != _modelCache.end()) {
        return it->second;
    }

    auto model = _createModel(textureId);
    _modelCache[textureId] = model;

    return model;
}

std::shared_ptr<raylib::Model> render::ResourceManager::getOrCreateModelFromFile(const std::string& path)
{
    auto it = _modelCache.find(path);
    if (it != _modelCache.end()) {
        return it->second;
    }

    auto model = std::make_shared<raylib::Model>(path.c_str());
    _modelCache[path] = model;

    return model;
}

Texture2D render::ResourceManager::_loadTexturePath(const std::string& path)
{
    Texture2D tex = LoadTexture(path.c_str());
    if (tex.id == 0) {
        std::cerr << "[ResourceManager] Failed to load texture: " << path << "\n";
    }
    return tex;
}

std::shared_ptr<raylib::Model> render::ResourceManager::_createModel(const std::string& textureId)
{
    auto model = std::make_shared<raylib::Model>(_baseMesh);

    Texture2D tex = _defaultTexture;

    auto it = common::textureMap.find(textureId);
    if (it != common::textureMap.end()) {
        Texture2D loaded = _loadTexturePath(it->second);
        if (loaded.id != 0)
            tex = loaded;
    }

    model->materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = tex;

    return model;
}
