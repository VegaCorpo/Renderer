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

    // Possède un triplet VAO/VBO/EBO. Ne connaît ni les matériaux, ni les
    // textures, ni la scène : uniquement le stockage GPU de la géométrie et
    // l'appel de dessin.
    class GLMesh {
        public:
            GLMesh() = default;
            ~GLMesh();

            GLMesh(const GLMesh&) = delete;
            GLMesh& operator=(const GLMesh&) = delete;
            GLMesh(GLMesh&& other) noexcept;
            GLMesh& operator=(GLMesh&& other) noexcept;

            void upload(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);

            void draw() const;

        private:
            void _release();

            unsigned int _vao = 0;
            unsigned int _vbo = 0;
            unsigned int _ebo = 0;
            std::size_t _indexCount = 0;
    };
} // namespace render
