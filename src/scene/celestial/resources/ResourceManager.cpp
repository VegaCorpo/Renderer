#include "ResourceManager.hpp"
#include <iostream>

render::ResourceManager::ResourceManager(std::shared_ptr<GLRenderer> renderer) : _renderer(std::move(renderer))
{
    this->_baseMesh = this->_renderer->loadMesh(UVSPHERE_MODEL_PATH);

    this->_modelCache[common::DEFAULT_TEXTURE_PATH] = this->_createModelInfoFromTexture(common::DEFAULT_TEXTURE_PATH);
}

std::shared_ptr<render::ModelInfo> render::ResourceManager::getOrCreateModelInfo(const std::string& textureId)
{
    auto it = this->_modelCache.find(textureId);
    if (it != this->_modelCache.end()) {
        return it->second;
    }

    auto info = _createModelInfoFromTexture(textureId);
    this->_modelCache[textureId] = info;

    return info;
}

render::TextureHandle render::ResourceManager::getDefaultTexture() const
{
    auto it = this->_modelCache.find(common::DEFAULT_TEXTURE_PATH);
    return it != this->_modelCache.end() ? it->second->texture : INVALID_TEXTURE;
}

std::shared_ptr<render::ModelInfo> render::ResourceManager::_createModelInfoFromTexture(const std::string& texturePath)
{
    std::string fullPath = common::TEXTURE_PATH + texturePath;
    TextureHandle tex = this->_renderer->loadTexture(fullPath);

    if (tex == INVALID_TEXTURE) {
        std::cerr << "[ResourceManager] Error loading " << fullPath << " — using default texture\n";
        return this->_modelCache.at(common::DEFAULT_TEXTURE_PATH);
    }

    auto info = std::make_shared<ModelInfo>();
    info->texture = tex;
    info->dominantColor = this->_renderer->getTextureDominantColor(tex);

    return info;
}
