#pragma once

#include <string>
#include <unordered_map>
#include "IRenderer.hpp"
#include "RenderTypes.hpp"

namespace render {
    class ARenderer : public IRenderer {
        public:
            ARenderer() = default;
            ~ARenderer() override = default;

            ARenderer(const ARenderer&) = delete;
            ARenderer& operator=(const ARenderer&) = delete;

            virtual bool initialize(const RendererConfig &config) override;

            [[nodiscard]] int getWidth() const override { return this->_width; }
            [[nodiscard]] int getHeight() const override { return this->_height; }
            void setWindowSize(int width, int height) override { this->_width = width; this->_height = height; }

            TextureHandle loadTexture(const std::string& filepath) override;
            void unloadTexture(TextureHandle handle) override;
            Color getTextureDominantColor(TextureHandle handle) const override;

            MeshHandle loadMesh(const std::string& filepath) override;
            void unloadMesh(MeshHandle handle) override;

        protected:
            virtual TextureHandle _loadTextureImpl(const std::string& filepath) = 0;
            virtual void _unloadTextureImpl(TextureHandle handle) = 0;
            virtual Color _computeDominantColorImpl(TextureHandle handle) const = 0;

            virtual MeshHandle _loadMeshImpl(const std::string& filepath) = 0;
            virtual void _unloadMeshImpl(MeshHandle handle) = 0;

            TextureHandle _nextTextureHandle() { return ++_textureHandleCounter; }
            MeshHandle _nextMeshHandle() { return ++_meshHandleCounter; }

            int _width = 0;
            int _height = 0;

        private:
            struct TextureEntry {
                    TextureHandle handle;
                    Color dominantColor;
            };

            std::unordered_map<std::string, TextureEntry> _textureCache; // filepath -> TextureEntry
            std::unordered_map<std::string, MeshHandle> _meshCache; // filepath -> MeshHandle

            TextureHandle _textureHandleCounter = 0;
            MeshHandle _meshHandleCounter = 0;
    };
} // namespace render
