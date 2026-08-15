#include "ARenderer.hpp"

bool render::ARenderer::initialize(const RendererConfig &config)
{
    this->setWindowSize(config.width, config.height);

    return true;
}

render::TextureHandle render::ARenderer::loadTexture(const std::string& filepath)
{
    auto it = _textureCache.find(filepath);
    if (it != _textureCache.end()) {
        return it->second.handle;
    }

    TextureHandle handle = _loadTextureImpl(filepath);
    if (handle == INVALID_TEXTURE) {
        return INVALID_TEXTURE;
    }

    _textureCache[filepath] = {handle, _computeDominantColorImpl(handle)};
    return handle;
}

void render::ARenderer::unloadTexture(TextureHandle handle)
{
    for (auto it = _textureCache.begin(); it != _textureCache.end(); ++it) {
        if (it->second.handle == handle) {
            _unloadTextureImpl(handle);
            _textureCache.erase(it);
            return;
        }
    }
}

render::Color render::ARenderer::getTextureDominantColor(TextureHandle handle) const
{
    for (auto& [path, entry] : _textureCache) {
        if (entry.handle == handle) {
            return entry.dominantColor;
        }
    }
    return Color{255, 255, 255, 255};
}

render::MeshHandle render::ARenderer::loadMesh(const std::string& filepath)
{
    auto it = _meshCache.find(filepath);
    if (it != _meshCache.end()) {
        return it->second;
    }

    MeshHandle handle = _loadMeshImpl(filepath);
    if (handle != INVALID_MESH) {
        _meshCache[filepath] = handle;
    }
    return handle;
}

void render::ARenderer::unloadMesh(MeshHandle handle)
{
    for (auto it = _meshCache.begin(); it != _meshCache.end(); ++it) {
        if (it->second == handle) {
            _unloadMeshImpl(handle);
            _meshCache.erase(it);
            return;
        }
    }
}
