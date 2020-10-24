#include "Tank.h"

#include "../Renderer/AnimatedSprite.h"



Tank::Tank(std::shared_ptr<Renderer::AnimatedSprite> pSprite, const glm::vec2& position, float velocity) :
           m_pSprite(std::move(pSprite)), m_position(position),
           m_velocity(velocity), m_move(false), m_direction(0.f, 1.f)
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
        m_position = m_position + m_velocity * deltaTime * m_direction;
        m_pSprite->setPosition(m_position);
        m_pSprite->update(deltaTime);
    }
}

void Tank::setSpriteState(const std::string& state)
{
    m_pSprite->setState(state);
}

