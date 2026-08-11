#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <utils/assets.hpp>
#include "renderer/ARenderer.hpp"

namespace render {
    inline const std::string UVSPHERE_MODEL_PATH = common::ASSETS_PATH + "models/UVSphere.obj";

    struct ModelInfo {
            TextureHandle texture = INVALID_TEXTURE;
            Color dominantColor{255, 255, 255, 255};
    };

    class ResourceManager {
        public:
            explicit ResourceManager(std::shared_ptr<ARenderer> renderer);
            ~ResourceManager() = default;

            [[nodiscard]] MeshHandle getBaseMesh() const { return _baseMesh; }

            std::shared_ptr<ModelInfo> getOrCreateModelInfo(const std::string& textureId);

            [[nodiscard]] TextureHandle getDefaultTexture() const;

        private:
            std::shared_ptr<ModelInfo> _createModelInfoFromTexture(const std::string& texturePath);

            std::shared_ptr<ARenderer> _renderer;

            std::unordered_map<std::string, std::shared_ptr<ModelInfo>> _modelCache;

            MeshHandle _baseMesh = INVALID_MESH;
    };
} // namespace render
