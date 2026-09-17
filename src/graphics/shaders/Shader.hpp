#pragma once

#include <Eigen/Dense>

namespace render {
    // Compile et lie un programme GLSL à partir de sources, et envoie les uniforms.
    // Ne connaît ni les meshes, ni la scène.
    class Shader {
        public:
            Shader() = default;
            ~Shader();

            Shader(const Shader&) = delete;
            Shader& operator=(const Shader&) = delete;
            Shader(Shader&& other) noexcept;
            Shader& operator=(Shader&& other) noexcept;

            [[nodiscard]] bool compile(const char* vertexSource, const char* fragmentSource);

            void use() const;

            void setMat4(const char* name, const Eigen::Matrix4f& value) const;
            void setVec3(const char* name, const Eigen::Vector3f& value) const;
            void setFloat(const char* name, float value) const;
            void setInt(const char* name, int value) const;

        private:
            [[nodiscard]] static unsigned int _compileStage(unsigned int stage, const char* source);
            [[nodiscard]] int _uniformLocation(const char* name) const;

            unsigned int _program = 0;
    };
} // namespace render
