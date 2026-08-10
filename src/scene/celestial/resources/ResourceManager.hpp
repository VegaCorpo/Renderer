#pragma once

#include <Texture.hpp>
#include <memory>
#include <Mesh.hpp>
#include <raylib.h>
#include <string>
#include <unordered_map>
#include <utils/assets.hpp>

namespace render {
    inline const std::string UVSPHERE_MODEL_PATH = common::ASSETS_PATH + "models/UVSphere.obj";

    struct ModelInfo {
            raylib::Texture2D texture;
            Color dominantColor;
    };

    class ResourceManager {
        public:
            ResourceManager();
            ~ResourceManager();

            const raylib::Model &getBaseModel() const { return _baseModel; }

            std::shared_ptr<ModelInfo> getOrCreateModelInfo(const std::string& textureId);

            Texture2D getDefaultTexture() const { return _defaultTexture; }
            void setDefaultTexture(Texture2D tex) { _defaultTexture = tex; }

        private:
            std::shared_ptr<ModelInfo> _createModelInfoFromTexture(const std::string& texturePath);
            static Color _computeDominantColor(const Texture2D& tex);

            std::unordered_map<std::string, std::shared_ptr<ModelInfo>> _modelCache;

            raylib::Model _baseModel;
            // raylib::Mesh _baseMesh;

            raylib::Texture2D _defaultTexture;
    };
} // namespace render
