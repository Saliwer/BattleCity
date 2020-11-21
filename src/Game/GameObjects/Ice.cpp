#include "Ice.h"
#include "Tank.h"
#include "../../Renderer/Sprite.h"
#include "../../Manager/ResourceManager.h"


Ice::Ice(const glm::vec2& position, const glm::vec2& size, float layer)
        : IStaticGameObject(position, size, layer)
{
    m_pSprite = ResourceManager::getSprite("ice8x8");
}

Ice::~Ice()
{}

void Ice::render() const
{
    m_pSprite->render(m_position, m_size, m_layer);
}

bool Ice::checkCollision(std::shared_ptr<IDynamicGameObject> dynObject, const glm::vec2& newPos)
{
    if (!hasIntersection(dynObject->getGlobalAABB()))
        return false;

    switch(dynObject->getType())
    {
        case IDynamicGameObject::EDynamicType::TankType1:
            dynObject->getPosition() = newPos;
            handlingCollision(static_cast<Tank*>(dynObject.get()));
            break;
        case IDynamicGameObject::EDynamicType::Bullet:
            return false;
        default:
            //std::cerr << "Ice: collision with unknown dynamic object\n";
            return false;
    }

    return true;
}

void Ice::handlingCollision(Tank* tank)
{
    tank->setCurrentSmooth(tank->getSlideSmooth());
}
