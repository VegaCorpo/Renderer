#pragma once

#include <memory>
#include <Mesh.hpp>
#include <raylib.h>
#include <string>
#include <unordered_map>

namespace render {
    struct ModelInfo {
            raylib::Model model;
            Color dominantColor;
    };

    class ResourceManager {
        public:
            ResourceManager();
            ~ResourceManager();

            std::shared_ptr<ModelInfo> getOrCreateModelInfo(const std::string& textureId);

            Texture2D getDefaultTexture() const { return _defaultTexture; }
            void setDefaultTexture(Texture2D tex) { _defaultTexture = tex; }

        private:
            std::shared_ptr<ModelInfo> _createModelInfoFromTexture(const std::string& texturePath);
            static Color _computeDominantColor(const Texture2D& tex);

            std::unordered_map<std::string, std::shared_ptr<ModelInfo>> _modelCache;

            Mesh _baseMesh;

            Texture2D _defaultTexture = {0};
    };
} // namespace render
