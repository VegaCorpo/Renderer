#include "ResourceManager.hpp"
#include <iostream>
#include <utils/assets.hpp>

render::ResourceManager::ResourceManager() : _baseMesh()
{
    this->_baseMesh = raylib::Mesh::Sphere(1, 32, 32);

    this->_modelCache[common::DEFAULT_TEXTURE_PATH] = this->_createModelFromTexture(common::DEFAULT_TEXTURE_PATH);
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

    auto model = _createModelFromTexture(textureId);
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

std::shared_ptr<raylib::Model> render::ResourceManager::_createModelFromTexture(const std::string& texturePath)
{
    std::string fullPath = common::TEXTURE_PATH + texturePath;
    Texture2D tex = LoadTexture(fullPath.c_str());

    if (tex.id == 0) {
        std::cerr << "[ResourceManager] Error loading " << fullPath << " — using default texture\n";
        return this->_modelCache["default.jpg"];
    }

    auto model = std::make_shared<raylib::Model>(_baseMesh);

    model->materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = tex;

    return model;
}
