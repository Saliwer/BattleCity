#include "Tree.h"

#include "../../Renderer/Sprite.h"
#include "../../Manager/ResourceManager.h"


Tree::Tree(const glm::vec2& position, const glm::vec2& size, float layer)
          : IStaticGameObject(position, size, layer)
{
    m_pSprite = ResourceManager::getSprite("tree8x8");
}

Tree::~Tree()
{}

void Tree::render() const
{
    m_pSprite->render(m_position, m_size, m_layer);
}

bool Tree::checkCollision(std::shared_ptr<IDynamicGameObject> dynObject, const glm::vec2& newPos)
{
    if (!hasIntersection(dynObject->getGlobalAABB()))
        return false;

    dynObject->setSpeed(dynObject->getMaxSpeed() * 0.6f);
    dynObject->getPosition() = newPos;
    return true;
}
