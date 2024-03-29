#include "AnimatedSprite.h"
#include <iostream>

namespace RenderEngine
{

AnimatedSprite::AnimatedSprite(std::shared_ptr<ShaderProgram> pShaderProg,
                               std::shared_ptr<Texture2D> pTexture,
                               std::string subTextureName,
                               std::vector<Frame> frames)
                               : Sprite(std::move(pShaderProg), std::move(pTexture), std::move(subTextureName))
                               , m_frames(std::move(frames))
                               , m_activeFrame(0)
                               , m_currentAnimationTime(0)
{
}

AnimatedSprite::~AnimatedSprite()
{
}

void AnimatedSprite::update(double delta)
{
    if (m_frames.empty())
        return;
    m_currentAnimationTime += delta;
    while (m_currentAnimationTime >= m_frames[m_activeFrame].m_currentFrameDuration)
    {
        m_currentAnimationTime -= m_frames[m_activeFrame].m_currentFrameDuration;
        ++m_activeFrame;
        if (m_activeFrame == m_frames.size())
        {
            m_activeFrame = 0;
        }
    }
    if (m_activeSubTexture != m_frames[m_activeFrame].m_subTextureName)
        setSubTexture(m_frames[m_activeFrame].m_subTextureName);
}


void AnimatedSprite::render(const glm::vec2& position, const glm::vec2& size, const glm::vec2& direction, float layer) const
{
    if (m_frames.empty())
        return;
    Sprite::render(position, size, direction, layer);
}

void AnimatedSprite::render(const glm::vec2& position, const glm::vec2& size, float layer) const
{
    if (m_frames.empty())
        return;
    Sprite::render(position, size, layer);
}

void AnimatedSprite::addFrame(std::string name, double duration)
{
    m_frames.emplace_back(std::move(name), duration);
}



}
