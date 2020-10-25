#include "Tank.h"

#include "../Renderer/AnimatedSprite.h"

extern glm::ivec2 g_WindowSize;

Tank::Tank(std::shared_ptr<Renderer::AnimatedSprite> pSprite, const glm::vec2& position, float velocity) :
           m_pSprite(std::move(pSprite)), m_position(position),
           m_velocity(velocity, velocity), m_move(false), m_direction(0.f, 1.f)
{
    m_pSprite->setPosition(m_position);
}

void Tank::render() const
{
    m_pSprite->render();
}

void Tank::update(uint64_t deltaTime)
{
    if (m_move)
    {
        //deltaTime in microseconds!
        float dt = deltaTime / 10000.f;
        m_position = m_position + dt * m_velocity * m_direction;
        if ((int)m_position.x + m_pSprite->getSize().x >= g_WindowSize.x)
            m_position.x = (float)g_WindowSize.x - m_pSprite->getSize().x;
        else if (m_position.x < 0.f)
            m_position.x = 0.f;
        if ((int)m_position.y + m_pSprite->getSize().y >= g_WindowSize.y)
            m_position.y = (float)g_WindowSize.y - m_pSprite->getSize().y;
        else if (m_position.y < 0.f)
            m_position.y = 0.f;
        m_pSprite->setPosition(m_position);
        m_pSprite->update(deltaTime);
    }
}

void Tank::setSpriteState(const std::string& state)
{
    m_pSprite->setState(state);
}

