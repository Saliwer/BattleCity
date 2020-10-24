#include "AnimatedSprite.h"
#include <iostream>

namespace Renderer
{

AnimatedSprite::AnimatedSprite(std::shared_ptr<ShaderProgram> pShaderProg,
                               std::shared_ptr<Texture2D> pTexture,
                               const glm::vec2& position,
                               const glm::vec2& size,
                               float rotation) :
                               Sprite(pShaderProg, pTexture, "",
                                      position, size, rotation),
                               m_currentSpriteDuration(0)
{
    m_activeState = m_states.end();
}

AnimatedSprite::~AnimatedSprite()
{
}

void AnimatedSprite::insertState(std::string name, ListTextures subTextures)
{
    m_states.emplace(std::move(name), std::move(subTextures));
}


void AnimatedSprite::setState(const std::string& newState)
{
    auto it = m_states.find(newState);
    if (it == m_states.end())
    {
        std::cerr << "AnimatedSprite: Couldn't find animation state '" <<
        newState << "'.\n";
        return;
    }

    if (it != m_activeState)
    {
        m_currentSpriteDuration = 0;
        m_activeState = it;
        m_activeSubTexture = m_activeState->second.cbegin();
        //current frame was changed
        setSubTexture(m_activeSubTexture->first);
    }
}

void AnimatedSprite::update(uint64_t delta)
{
    if (m_activeState == m_states.end())
        return;
    m_currentSpriteDuration+=delta;
    if (m_currentSpriteDuration >= m_activeSubTexture->second)
    {
        if(++m_activeSubTexture == m_activeState->second.cend())
            m_activeSubTexture = m_activeState->second.cbegin();
        m_currentSpriteDuration = 0;
    }
}


void AnimatedSprite::render()
{
    if (m_activeState == m_states.end())
        return;
    if((m_currentSpriteDuration == 0) && (m_activeState->second.size() != 0))
    {
      //current frame was changed
      setSubTexture(m_activeSubTexture->first);
    }
    Sprite::render();
}





}
