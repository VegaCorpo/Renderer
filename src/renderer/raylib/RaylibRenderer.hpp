#pragma once

#include <GLFW/glfw3.h>
#include <raylib-cpp.hpp>
#include <raylib.h>
#include "ARenderer.hpp"

namespace render {
    constexpr TraceLogLevel LOG_LEVEL = LOG_ERROR;

    class RaylibRenderer : public ARenderer {
        public:
            RaylibRenderer() = default;
            ~RaylibRenderer() override;

            bool initialize(const RendererConfig& config) override;
            void shutdown() override;

            void clear(Color color) override { ClearBackground(_toRaylibColor(color)); }
            void beginFrame() override { BeginDrawing(); }
            void endFrame() override { EndDrawing(); }

            void beginMode3D(const CameraView& camera) override;
            void endMode3D() override { ::EndMode3D(); }

            [[nodiscard]] bool windowShouldClose() const override { return WindowShouldClose(); }
            void* getWindowHandle() override { return glfwGetCurrentContext(); }

            void drawMesh(MeshHandle mesh, TextureHandle texture, const Vector3& position, float scale) override;
            void drawLine3D(const Vector3& start, const Vector3& end, Color color) override;

        protected:
            TextureHandle _loadTextureImpl(const std::string& filepath) override;
            void _unloadTextureImpl(TextureHandle handle) override {}
            Color _computeDominantColorImpl(TextureHandle handle) const override;

            MeshHandle _loadMeshImpl(const std::string& filepath) override;
            void _unloadMeshImpl(MeshHandle handle) override {}

        private:
            std::unordered_map<TextureHandle, Texture2D> _textures;
            std::unordered_map<MeshHandle, raylib::Model> _models;

            static raylib::Color _toRaylibColor(Color c) { return raylib::Color{c.r, c.g, c.b, c.a}; }
            static raylib::Vector3 _toRaylibVec3(const Vector3& v) { return raylib::Vector3{v.x, v.y, v.z}; }
    };
} // namespace render
