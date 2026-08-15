#pragma once

#include <string>
#include "RenderTypes.hpp"

namespace render {
    class IRenderer {
        public:
            virtual ~IRenderer() = default;

            virtual bool initialize(const RendererConfig &config) = 0;
            virtual void shutdown() = 0;

            [[nodiscard]] virtual int getWidth() const = 0;
            [[nodiscard]] virtual int getHeight() const = 0;
            virtual void setWindowSize(int width, int height) = 0;

            virtual void clear(Color color) = 0;
            virtual void beginFrame() = 0;
            virtual void endFrame() = 0;

            virtual void beginMode3D(const CameraView& camera) = 0;
            virtual void endMode3D() = 0;

            [[nodiscard]] virtual bool windowShouldClose() const = 0;
            virtual void* getWindowHandle() = 0;

            virtual TextureHandle loadTexture(const std::string& filepath) = 0;
            virtual void unloadTexture(TextureHandle handle) = 0;
            [[nodiscard]] virtual Color getTextureDominantColor(TextureHandle handle) const = 0;

            virtual MeshHandle loadMesh(const std::string& filepath) = 0;
            virtual void unloadMesh(MeshHandle handle) = 0;

            virtual void drawMesh(MeshHandle mesh, TextureHandle texture, const Vector3& position, float scale) = 0;
            virtual void drawLine3D(const Vector3& start, const Vector3& end, Color color) = 0;
    };
} // namespace render
