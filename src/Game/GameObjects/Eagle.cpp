#include "Eagle.h"

#include "../../Renderer/Sprite.h"
#include "../../Manager/ResourceManager.h"


Eagle::Eagle(bool isAlive, const glm::vec2& position, const glm::vec2& size, float layer)
            : m_isAlive(isAlive)
            , IStaticGameObject(position, size, layer)
{
    m_pAliveSprite = ResourceManager::getSprite("eagle");
    m_pDeadSprite = ResourceManager::getSprite("deadEagle");
}

Eagle::~Eagle()
{}

void Eagle::render() const
{
    if (m_isAlive)
        m_pAliveSprite->render(m_position, m_size, m_layer);
    else
        m_pDeadSprite->render(m_position, m_size, m_layer);
}

bool Eagle::checkCollision(std::shared_ptr<IDynamicGameObject> dynObject, const glm::vec2& newPosition)
{
    return false;
}
