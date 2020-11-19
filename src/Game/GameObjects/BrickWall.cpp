#include "BrickWall.h"

#include "../../Renderer/Sprite.h"
#include "../../Manager/ResourceManager.h"
#include "Tank.h"
#include "Bullet.h"


BrickWall::BrickWall(EBrickWallState brickWallState,
                     const glm::vec2& position, const glm::vec2& size, float layer)
                     : m_eCurrentBrickState(brickWallState)
                     , IStaticGameObject(position, size, layer)
{
    m_pSprites[static_cast<size_t>(EBrickWallState::fullBrick)]     = ResourceManager::getSprite("fullBrick8x8");
    m_pSprites[static_cast<size_t>(EBrickWallState::topBrick)]      = ResourceManager::getSprite("topBrick8x8");
    m_pSprites[static_cast<size_t>(EBrickWallState::bottomBrick)]   = ResourceManager::getSprite("bottomBrick8x8");
}

BrickWall::~BrickWall()
{}

void BrickWall::render() const
{
    if (m_eCurrentBrickState == EBrickWallState::destroyed)
        return;
    m_pSprites[static_cast<size_t>(m_eCurrentBrickState)]->render(m_position, m_size, m_layer);
}

bool BrickWall::checkCollision(std::shared_ptr<IDynamicGameObject> dynObject, const glm::vec2& newPos)
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
            //std::cerr << "BrickWall: collision with unknown dynamic object\n";
            return false;
    }
    return true;
}

void BrickWall::handlingCollision(Tank* tank)
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

void BrickWall::handlingCollision(Bullet* bullet)
{
    if (bullet->decLives() <= 0)
        bullet->setLive(false);
}
