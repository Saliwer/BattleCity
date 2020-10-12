#pragma once

#include <glad/glad.h>
#include <string>

namespace Renderer{

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
        void Use() const { glUseProgram(m_ID); }

    private:
        bool createShader(const char* shaderSource, GLenum shaderType, GLuint& shaderID);
    };
}
