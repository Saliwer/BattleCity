#include "Water.h"

#include "../../Renderer/AnimatedSprite.h"
#include "../../Manager/ResourceManager.h"


Water::Water(const glm::vec2& position, const glm::vec2& size, float layer)
            : IStaticGameObject(position, size, layer)
{
    m_pSprite = ResourceManager::getAnimatedSprite("water");
}

Water::~Water()
{}

void Water::render() const
{
    m_pSprite->render(m_position, m_size, m_layer);
}

void Water::update(double delta)
{
    m_pSprite->update(delta);
}

bool Water::checkCollision(std::shared_ptr<IDynamicGameObject> dynObject, const glm::vec2& newPos)
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
