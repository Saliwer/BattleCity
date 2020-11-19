#include "Eagle.h"
#include "Bullet.h"
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
    if (!hasIntersection(dynObject->getGlobalAABB()))
        return false;

    switch(dynObject->getType())
    {
        case IDynamicGameObject::EDynamicType::TankType1:
            return false;
        case IDynamicGameObject::EDynamicType::Bullet:
            handlingCollision(static_cast<Bullet*>(dynObject.get()));
            break;
        default:
            //std::cerr << "Eagle: collision with unknown dynamic object\n";
            return false;
    }
    return true;
}

void Eagle::handlingCollision(Tank* tank)
{
}

void Eagle::handlingCollision(Bullet* bullet)
{
    bullet->setLive(false);
    m_isAlive = false;
}

