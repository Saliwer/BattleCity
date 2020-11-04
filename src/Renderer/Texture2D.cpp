#include "Texture2D.h"

namespace RenderEngine{

Texture2D::Texture2D(int width, int height, int channels, unsigned char* data,
                    GLenum wrap, GLenum filter) : m_width(width), m_height (height)
{
    glGenTextures(1, &m_ID);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);

    switch(channels)
    {
    case 3:
        m_mode = GL_RGB;
        break;
    case 4:
        m_mode = GL_RGBA;
        break;
    default:
        m_mode = GL_RGBA;
        break;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, m_mode, m_width, m_height, 0, m_mode, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture2D::~Texture2D()
{
    glDeleteTextures(1, &m_ID);
}

Texture2D::Texture2D(Texture2D&& other) noexcept
{
    m_ID = other.m_ID;
    m_mode = other.m_mode;
    m_width = other.m_width;
    m_height = other.m_height;
    other.m_ID = 0;
}

Texture2D& Texture2D::operator=(Texture2D&& other) noexcept
{
    glDeleteTextures(1, &m_ID);
    m_ID = other.m_ID;
    m_mode = other.m_mode;
    m_width = other.m_width;
    m_height = other.m_height;
    other.m_ID = 0;
    return *this;
}

void Texture2D::bind() const
{
    if (m_ID)
        glBindTexture(GL_TEXTURE_2D, m_ID);
}

void Texture2D::unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::addSubTexture(const std::string& name, const glm::vec2& leftBottomUV,
                              const glm::vec2& rightTopUV)
{
    auto res = m_subTextures.emplace(name, SubTexture(leftBottomUV, rightTopUV));
    if (!res.second)
        return;
}

void Texture2D::addSubTexture(std::string&& name, glm::vec2&& leftBottomUV,
                              glm::vec2&& rightTopUV)
{
    auto res = m_subTextures.emplace(std::move(name), SubTexture(leftBottomUV, rightTopUV));
    if (!res.second)
        return;
}


const SubTexture& Texture2D::getSubTexture(const std::string& name)
{
    auto it = m_subTextures.find(name);
    if (it != m_subTextures.end())
        return it->second;
    const static SubTexture defaultSubTexture;
    return defaultSubTexture;
}

void Texture2D::genSubTextures(const std::vector<std::string>& names, const glm::vec2& leftTop,
                               const glm::vec2& sizeSubTexture)
{
    float coordX = leftTop.x;
    float coordY = leftTop.y;

    for (const auto& subText : names)
    {
        glm::vec2 leftUV(static_cast<float>((coordX + 0.0005f) / getWidth()),
                         static_cast<float>((coordY + 0.0005f - sizeSubTexture.y) / getHeight()));
        glm::vec2 rightUV(static_cast<float>((coordX - 0.0005f + sizeSubTexture.x) / getWidth()),
                          static_cast<float>((coordY - 0.0005f) / getHeight()));
        addSubTexture(subText, leftUV, rightUV);
        coordX+= sizeSubTexture.x;
        if (coordX >= getWidth())
        {
            coordX = leftTop.x;
            coordY -= sizeSubTexture.y;
        }
    }
}

void Texture2D::genSubTextures(std::vector<std::string>&& names, glm::vec2&& leftTop,
                               glm::vec2&& sizeSubTexture)
{
    float coordX = leftTop.x;
    float coordY = leftTop.y;

    for (auto& subText : names)
    {
        glm::vec2 leftUV(static_cast<float>((coordX + 0.0005f) / getWidth()),
                         static_cast<float>((coordY + 0.0005f - sizeSubTexture.y) / getHeight()));
        glm::vec2 rightUV(static_cast<float>((coordX - 0.0005f + sizeSubTexture.x) / getWidth()),
                          static_cast<float>((coordY - 0.0005f) / getHeight()));
        addSubTexture(std::move(subText), std::move(leftUV), std::move(rightUV));
        coordX+= sizeSubTexture.x;
        if (coordX >= getWidth())
        {
            coordX = leftTop.x;
            coordY -= sizeSubTexture.y;
        }
    }
}

}
