#include "BetonWall.h"
#include "Tank.h"
#include "Bullet.h"
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

    switch(dynObject->getType())
    {
        case IDynamicGameObject::EDynamicType::TankType1:
            handlingCollision(static_cast<Tank*>(dynObject.get()));
            break;
        case IDynamicGameObject::EDynamicType::Bullet:
            handlingCollision(static_cast<Bullet*>(dynObject.get()));
            break;
        default:
            //std::cerr << "BetonWall: collision with unknown dynamic object\n";
            return false;
    }
    return true;
}

void BetonWall::handlingCollision(Tank* tank)
{
    if (tank->getDirection().x > 0.f)
        tank->getPosition().x = m_position.x - tank->getSize().x;
    else if (tank->getDirection().x < 0.f)
        tank->getPosition().x = m_position.x + m_size.x;
    else if (tank->getDirection().y > 0.f)
        tank->getPosition().y = m_position.y - tank->getSize().y;
    else if (tank->getDirection().y < 0.f)
        tank->getPosition().y = m_position.y + m_size.y;
}

void BetonWall::handlingCollision(Bullet* bullet)
{
    if (bullet->decLives() <= 0)
        bullet->setLive(false);
}
