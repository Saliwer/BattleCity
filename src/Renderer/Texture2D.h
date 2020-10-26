#pragma once

#include "glad/glad.h"
#include "glm/vec2.hpp"
#include <string>
#include <map>
#include <vector>

namespace RenderEngine{

struct SubTexture
{
    glm::vec2 leftBottomUV;
    glm::vec2 rightTopUV;

    SubTexture(const glm::vec2& _leftBottomUV = glm::vec2(0.f),
               const glm::vec2& _rightTopUV = glm::vec2(1.f)) :
               leftBottomUV(_leftBottomUV), rightTopUV(_rightTopUV)
    {}
};

class Texture2D{
public:

    Texture2D(int width, int height, int channels, unsigned char* data,
              GLenum wrap = GL_CLAMP_TO_EDGE, GLenum filter = GL_LINEAR);
    ~Texture2D();
    Texture2D(Texture2D&& other) noexcept;
    Texture2D& operator=(Texture2D&& other) noexcept;

    Texture2D(const Texture2D&) = delete;
    Texture2D& operator=(const Texture2D&) = delete;

    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }
    void bind() const;
    void unbind() const;

    void addSubTexture(const std::string& name, const glm::vec2& leftBottomUV,
                       const glm::vec2& rightTopUV);

    void addSubTexture(std::string&& name, glm::vec2&& leftBottomUV,
                       glm::vec2&& rightTopUV);

    void genSubTextures(const std::vector<std::string>& names, const glm::vec2& leftTop,
                        const glm::vec2& sizeSubTexture);

    void genSubTextures(std::vector<std::string>&& names, glm::vec2&& leftTop,
                        glm::vec2&& sizeSubTexture);



    const SubTexture& getSubTexture(const std::string& name);

private:
    int                                 m_width;
    int                                 m_height;
    GLuint                              m_ID;
    GLenum                              m_mode;
    std::map<std::string, SubTexture>   m_subTextures;
};


}
