#include "Tree.h"
#include "Tank.h"
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

    switch(dynObject->getType())
    {
        case IDynamicGameObject::EDynamicType::TankType1:
            handlingCollision(static_cast<Tank*>(dynObject.get()));
            dynObject->getPosition() = newPos;
            break;
        case IDynamicGameObject::EDynamicType::Bullet:
            return false;
        default:
            //std::cerr << "Tree: collision with unknown dynamic object\n";
            return false;
    }
    return true;
}

void Tree::handlingCollision(Tank* tank)
{
    tank->setSpeed(tank->getMaxSpeed() * 0.6f);
}
