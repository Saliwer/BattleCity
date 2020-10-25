#pragma once

#include <glad/glad.h>
#include <string>
#include <glm/mat4x4.hpp>

namespace RenderEngine{

    class ShaderProgram{
        GLuint m_ID;
        bool m_isCompiled;

    public:
        ShaderProgram() = delete;
        ShaderProgram(const ShaderProgram&) = delete;
        ShaderProgram& operator=(const ShaderProgram&) = delete;

        ShaderProgram(const std::string& vertexSource, const std::string& fragmentSource);
        ShaderProgram(ShaderProgram&& other) noexcept;
        ShaderProgram& operator=(ShaderProgram&& other) noexcept;
        ~ShaderProgram();

        bool isCompiled() const { return m_isCompiled; }
        void use() const { glUseProgram(m_ID); }
        void unUse() const { glUseProgram(0); }

        void setUniform(const std::string& name, int value);
        void setUniform(const std::string& name, GLfloat value);
        void setUniform(const std::string& name, GLfloat x, GLfloat y);
        void setUniform(const std::string& name, const glm::mat4& matrix);
    private:
        GLuint getUniformLocation(const std::string& name);
        bool createShader(const char* shaderSource, GLenum shaderType, GLuint& shaderID);
    };
}
