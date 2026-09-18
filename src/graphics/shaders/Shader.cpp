#include "Shader.hpp"
#include <glad/gl.h>
#include <iostream>
#include <utility>

render::Shader::~Shader()
{
    if (_program != 0)
        glDeleteProgram(_program);
}

render::Shader::Shader(Shader&& other) noexcept : _program(std::exchange(other._program, 0))
{}

render::Shader& render::Shader::operator=(Shader&& other) noexcept
{
    if (this != &other) {
        if (_program != 0)
            glDeleteProgram(_program);
        _program = std::exchange(other._program, 0);
    }
    return *this;
}

unsigned int render::Shader::_compileStage(unsigned int stage, const char* source)
{
    unsigned int id = glCreateShader(stage);
    glShaderSource(id, 1, &source, nullptr);
    glCompileShader(id);

    int success = 0;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success) {
        char log[512];
        glGetShaderInfoLog(id, sizeof(log), nullptr, log);
        std::cerr << "[Shader] compile error: " << log << "\n";
        glDeleteShader(id);
        return 0;
    }
    return id;
}

bool render::Shader::compile(const char* vertexSource, const char* fragmentSource)
{
    unsigned int vertex = _compileStage(GL_VERTEX_SHADER, vertexSource);
    unsigned int fragment = _compileStage(GL_FRAGMENT_SHADER, fragmentSource);

    if (vertex == 0 || fragment == 0) {
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        return false;
    }

    _program = glCreateProgram();
    glAttachShader(_program, vertex);
    glAttachShader(_program, fragment);
    glLinkProgram(_program);

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    int success = 0;
    glGetProgramiv(_program, GL_LINK_STATUS, &success);
    if (!success) {
        char log[512];
        glGetProgramInfoLog(_program, sizeof(log), nullptr, log);
        std::cerr << "[Shader] link error: " << log << "\n";
        return false;
    }
    return true;
}

void render::Shader::bindUniformBlock(const char* blockName, unsigned int bindingPoint) const
{
    unsigned int index = glGetUniformBlockIndex(this->_program, blockName);

    if (index != GL_INVALID_INDEX) {
        glUniformBlockBinding(this->_program, index, bindingPoint);
    }
}

void render::Shader::use() const
{
    glUseProgram(_program);
}

int render::Shader::_uniformLocation(const char* name) const
{
    if (auto it = this->_uniformCache.find(name); it != this->_uniformCache.end()) {
        return it->second;
    }

    int location = glGetUniformLocation(this->_program, name);
    this->_uniformCache[name] = location;
    return location;
}

void render::Shader::setMat4(const char* name, const Eigen::Matrix4f& value) const
{
    glUniformMatrix4fv(_uniformLocation(name), 1, GL_FALSE, value.data());
}

void render::Shader::setVec3(const char* name, const Eigen::Vector3f& value) const
{
    glUniform3f(_uniformLocation(name), value.x(), value.y(), value.z());
}

void render::Shader::setFloat(const char* name, float value) const
{
    glUniform1f(_uniformLocation(name), value);
}

void render::Shader::setInt(const char* name, int value) const
{
    glUniform1i(_uniformLocation(name), value);
}
