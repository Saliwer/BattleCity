#include "ShaderProgram.h"

#include <iostream>

namespace Renderer{

ShaderProgram::ShaderProgram(const std::string& vertexSource, const std::string& fragmentSource) :
    m_isCompiled(false)
{
    GLuint vertexID = 0;
    if (!createShader(vertexSource.c_str(), GL_VERTEX_SHADER, vertexID))
    {
        std::cerr << "ERROR::VERTEX SHADER COMPILATION" << std::endl;
        return;
    }

    GLuint fragmentID = 0;
    if (!createShader(fragmentSource.c_str(), GL_FRAGMENT_SHADER, fragmentID))
    {
        std::cerr << "ERROR::FRAGMENT SHADER COMPILATION" << std::endl;
        glDeleteShader(vertexID);
        return;
    }

    m_ID = glCreateProgram();
    glAttachShader(m_ID, vertexID);
    glAttachShader(m_ID, fragmentID);

    glLinkProgram(m_ID);

    GLint success;
    glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[1024];
        glGetProgramInfoLog(m_ID, 1024, nullptr, infoLog);
        std::cout << "ERROR::SHADER PROGRAM::LINKING FAILED\n" << infoLog << std::endl;
    }
    else
        m_isCompiled = true;
    glDeleteShader(vertexID);
    glDeleteShader(fragmentID);
}

ShaderProgram::ShaderProgram(ShaderProgram&& other) noexcept
{
    m_ID = other.m_ID;
    m_isCompiled = other.m_isCompiled;
    other.m_ID = 0;
    other.m_isCompiled = false;
}

ShaderProgram& ShaderProgram::operator=(ShaderProgram&& other) noexcept
{
    if (!m_ID)
        glDeleteProgram(m_ID);
    m_ID = other.m_ID;
    m_isCompiled = other.m_isCompiled;
    other.m_ID = 0;
    other.m_isCompiled = false;
    return *this;
}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(m_ID);
}

bool ShaderProgram::createShader(const char* shaderSource, GLenum shaderType, GLuint& shaderID)
{
    shaderID = glCreateShader(shaderType);
    glShaderSource(shaderID, 1, &shaderSource, nullptr);
    glCompileShader(shaderID);

    GLint success;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[1024];
        glGetShaderInfoLog(shaderID, 1024, nullptr, infoLog);
        std::cerr << "ERROR::SHADER_COMPILATION\n" << infoLog << std::endl;
        return false;
    }
    return true;
}

}
