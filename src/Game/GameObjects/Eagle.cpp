#include "Eagle.h"

#include "../../Renderer/Sprite.h"
#include "../../Manager/ResourceManager.h"


Eagle::Eagle(bool isAlive, const glm::vec2& position, const glm::vec2& size,
             const glm::vec2& direction) : m_isAlive(isAlive), IGameObject(position, size, direction)
{
    m_pAliveSprite = ResourceManager::getSprite("eagle");
    m_pDeadSprite = ResourceManager::getSprite("deadEagle");
}

Eagle::~Eagle()
{}

void Eagle::render() const
{
    if (m_isAlive)
        m_pAliveSprite->render(m_position, m_size, m_direction);
    else
        m_pDeadSprite->render(m_position, m_size, m_direction);
}
