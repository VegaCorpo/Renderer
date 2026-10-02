#pragma once

#include <cstddef>
#include <Eigen/Dense>
#include <vector>

namespace render {
    struct Vertex {
            Eigen::Vector3f position;
            Eigen::Vector3f normal;
            Eigen::Vector2f uv;
    };

    // Owns a VAO/VBO/EBO triplet plus an optional per-instance model-matrix
    // buffer. Knows nothing about materials, textures, or the scene — only
    // GPU-side geometry storage and (instanced) draw calls.
    class GLMesh {
        public:
            GLMesh() = default;
            ~GLMesh();

            GLMesh(const GLMesh&) = delete;
            GLMesh& operator=(const GLMesh&) = delete;
            GLMesh(GLMesh&& other) noexcept;
            GLMesh& operator=(GLMesh&& other) noexcept;

            void upload(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
            void setupInstancing();
            void updateInstances(const std::vector<Eigen::Matrix4f>& models);

            void draw() const;
            void drawInstanced(std::size_t instanceCount) const;

        private:
            void _release();

            unsigned int _vao = 0;
            unsigned int _vbo = 0;
            unsigned int _ebo = 0;
            unsigned int _instanceVbo = 0;
            std::size_t _indexCount = 0;
    };
} // namespace render
