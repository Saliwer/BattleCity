#include "Tank.h"

#include "../../Renderer/AnimatedSprite.h"

#include <iostream>
#include "../../Manager/ResourceManager.h"

extern glm::ivec2 g_WindowSize;

Tank::Tank(const glm::vec2& position, const glm::vec2& size,
           const glm::vec2& direction, float velocity) :
           IGameObject(position, size, glm::normalize(direction)),
           m_pSprite(ResourceManager::getAnimatedSprite("tankYellowType1AnimSprite")),
           m_velocity(velocity, velocity), m_move(false)
{
}

void Tank::render() const
{
    m_pSprite->render(m_position, m_size, m_direction);
}

void Tank::update(uint64_t deltaTime)
{
    if (m_move)
    {
        //deltaTime in microseconds!
        float dt = deltaTime / 10000.f;
        m_position = m_position + dt * m_velocity * m_direction;
        if ((int)m_position.x + m_size.x >= g_WindowSize.x)
            m_position.x = (float)g_WindowSize.x - m_size.x;
        else if (m_position.x < 0.f)
            m_position.x = 0.f;
        if ((int)m_position.y + m_size.y >= g_WindowSize.y)
            m_position.y = (float)g_WindowSize.y - m_size.y;
        else if (m_position.y < 0.f)
            m_position.y = 0.f;
        m_pSprite->update(deltaTime);
    }
}

void Tank::setSpriteState(const std::string& state)
{
    m_pSprite->setState(state);
}

