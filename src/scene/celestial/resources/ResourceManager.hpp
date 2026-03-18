#pragma once

#include <memory>
#include <Mesh.hpp>
#include <raylib.h>
#include <string>
#include <unordered_map>

namespace render {
    class ResourceManager {
        public:
            ResourceManager();
            ~ResourceManager();

            std::shared_ptr<raylib::Model> getOrCreateModel(const std::string& textureId);
            std::shared_ptr<raylib::Model> getOrCreateModelFromFile(const std::string& path);

            Texture2D getDefaultTexture() const { return _defaultTexture; }
            void setDefaultTexture(Texture2D tex) { _defaultTexture = tex; }

        private:
            std::shared_ptr<raylib::Model> _createModelFromTexture(const std::string& texturePath);

            std::unordered_map<std::string, std::shared_ptr<raylib::Model>> _modelCache;

            Mesh _baseMesh;

            Texture2D _defaultTexture = {0};
    };
} // namespace render
