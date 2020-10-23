#include "AnimatedSprite.h"


namespace Renderer
{

AnimatedSprite::AnimatedSprite(std::shared_ptr<ShaderProgram> pShaderProg,
                               std::shared_ptr<Texture2D> pTexture,
                               const glm::vec2& position,
                               const glm::vec2& size,
                               float rotation) :
                               Sprite(pShaderProg, pTexture,
                                      "Default", position,
                                       size, rotation)
{
    m_currentSpriteDuration = 0;
    m_activeSprite = m_subTextures.end();
}

AnimatedSprite::~AnimatedSprite()
{
}


void AnimatedSprite::addSubTexture(const std::string& name, uint64_t duration)
{
    m_subTextures.emplace_back(std::make_pair(name, duration));
    if (m_activeSprite == m_subTextures.end())
        {
            m_activeSprite = m_subTextures.begin();
            setSubTexture(m_activeSprite->first);
        }
}

void AnimatedSprite::update(uint64_t delta)
{
    if (m_activeSprite == m_subTextures.end())
        return;
    m_currentSpriteDuration+=delta;
    if (m_currentSpriteDuration >= m_activeSprite->second)
    {
        if(++m_activeSprite == m_subTextures.end())
            m_activeSprite = m_subTextures.begin();
        m_currentSpriteDuration = 0;
    }
}


void AnimatedSprite::render()
{
    if (m_activeSprite == m_subTextures.end())
        return;
    if((m_currentSpriteDuration == 0) && (m_subTextures.size() != 0))
    {
      //current frame was changed
      setSubTexture(m_activeSprite->first);
    }
    Sprite::render();
}





}
