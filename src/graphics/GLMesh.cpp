#include "GLMesh.hpp"
#include <glad/gl.h>
#include <utility>

render::GLMesh::~GLMesh()
{
    _release();
}

render::GLMesh::GLMesh(GLMesh&& other) noexcept :
    _vao(std::exchange(other._vao, 0)), _vbo(std::exchange(other._vbo, 0)), _ebo(std::exchange(other._ebo, 0)),
    _indexCount(std::exchange(other._indexCount, 0))
{}

render::GLMesh& render::GLMesh::operator=(GLMesh&& other) noexcept
{
    if (this != &other) {
        _release();
        this->_vao = std::exchange(other._vao, 0);
        this->_vbo = std::exchange(other._vbo, 0);
        this->_ebo = std::exchange(other._ebo, 0);
        this->_indexCount = std::exchange(other._indexCount, 0);
    }
    return *this;
}

void render::GLMesh::_release()
{
    if (this->_ebo) {
        glDeleteBuffers(1, &this->_ebo);
    }
    if (this->_vbo) {
        glDeleteBuffers(1, &this->_vbo);
    }
    if (this->_vao) {
        glDeleteVertexArrays(1, &this->_vao);
    }
    this->_vao = this->_vbo = this->_ebo = 0;
}

void render::GLMesh::upload(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
{
    _release();

    glGenVertexArrays(1, &this->_vao);
    glGenBuffers(1, &this->_vbo);
    glGenBuffers(1, &this->_ebo);

    glBindVertexArray(this->_vao);

    glBindBuffer(GL_ARRAY_BUFFER, this->_vbo);
    glBufferData(GL_ARRAY_BUFFER, static_cast<long>(vertices.size() * sizeof(Vertex)), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<long>(indices.size() * sizeof(unsigned int)), indices.data(),
                 GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          reinterpret_cast<void*>(offsetof(Vertex, position)));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, normal)));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, uv)));

    glBindVertexArray(0);

    _indexCount = indices.size();
}

void render::GLMesh::draw() const
{
    if (this->_vao == 0)
        return;

    glBindVertexArray(this->_vao);
    glDrawElements(GL_TRIANGLES, static_cast<int>(_indexCount), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}
