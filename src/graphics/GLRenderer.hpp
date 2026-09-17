#pragma once

#include <string>
#include <unordered_map>
#include "GLContext.hpp"
#include "GLMesh.hpp"
#include "GLTexture.hpp"
#include "RenderTypes.hpp"
#include "Shader.hpp"
#include "models/ModelLoader.hpp"

namespace render {
    class GLRenderer {
        public:
            GLRenderer() = default;
            ~GLRenderer() = default;

            GLRenderer(const GLRenderer&) = delete;
            GLRenderer& operator=(const GLRenderer&) = delete;

            [[nodiscard]] bool initialize(const RendererConfig& config);
            void shutdown();

            [[nodiscard]] int getWidth() const { return _context.getWidth(); }
            [[nodiscard]] int getHeight() const { return _context.getHeight(); }

            void clear(Color color) const;
            void beginFrame() const { _context.pollEvents(); }
            void endFrame() const { _context.swapBuffers(); }

            [[nodiscard]] bool windowShouldClose() const { return _context.shouldClose(); }
            [[nodiscard]] void* getWindowHandle() const { return _context.getNativeHandle(); }

            void beginMode3D(const CameraView& camera);
            void endMode3D() {}

            [[nodiscard]] TextureHandle loadTexture(const std::string& filepath);
            [[nodiscard]] Color getTextureDominantColor(TextureHandle handle) const;

            [[nodiscard]] MeshHandle loadMesh(const std::string& filepath);

            void drawMesh(MeshHandle mesh, TextureHandle texture, const Eigen::Vector3f& position, float scale);
            void drawLine3D(const Eigen::Vector3f& start, const Eigen::Vector3f& end, Color color);

            // TODO: not implemented yet — needs a font atlas + glyph quads.
            void drawText(const std::string& text, const Eigen::Vector2f& screenPosition, Color color);

        private:
            [[nodiscard]] bool _loadShaders();
            void _createLineBuffers();

            GLContext _context;
            ModelLoader _modelLoader;

            Shader _meshShader;
            Shader _lineShader;

            unsigned int _lineVao = 0;
            unsigned int _lineVbo = 0;

            std::unordered_map<std::string, TextureHandle> _texturePathCache;
            std::unordered_map<TextureHandle, TextureData> _textures;
            TextureHandle _nextTextureHandle = INVALID_TEXTURE;

            std::unordered_map<std::string, MeshHandle> _meshPathCache;
            std::unordered_map<MeshHandle, GLMesh> _meshes;
            MeshHandle _nextMeshHandle = INVALID_MESH;

            Eigen::Matrix4f _viewMatrix = Eigen::Matrix4f::Identity();
            Eigen::Matrix4f _projMatrix = Eigen::Matrix4f::Identity();
    };
} // namespace render
