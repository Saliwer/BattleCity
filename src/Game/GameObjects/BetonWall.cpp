#include "BetonWall.h"

#include "../../Renderer/Sprite.h"
#include "../../Manager/ResourceManager.h"


BetonWall::BetonWall(EBetonWallState betonWallState,
                     const glm::vec2& position, const glm::vec2& size, float layer)
                     : m_eCurrentBetonState(betonWallState)
                     , IStaticGameObject(position, size, layer)
{
    m_pSprite = ResourceManager::getSprite("beton8x8");
}

BetonWall::~BetonWall()
{}

void BetonWall::render() const
{
    if (m_eCurrentBetonState != EBetonWallState::Destroyed)
        m_pSprite->render(m_position, m_size, m_layer);
}

bool BetonWall::checkCollision(std::shared_ptr<IDynamicGameObject> dynObject, const glm::vec2& newPos)
{
    if (!hasIntersection(dynObject->getGlobalAABB()))
        return false;
    if (dynObject->getDirection().x > 0.f)
        dynObject->getPosition().x = m_position.x - dynObject->getSize().x;
    else if (dynObject->getDirection().x < 0.f)
        dynObject->getPosition().x = m_position.x + m_size.x;
    else if (dynObject->getDirection().y > 0.f)
        dynObject->getPosition().y = m_position.y - dynObject->getSize().y;
    else if (dynObject->getDirection().y < 0.f)
        dynObject->getPosition().y = m_position.y + m_size.y;
    return true;
}
