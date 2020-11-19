#include "Bullet.h"
#include "../../Renderer/Sprite.h"
#include "../../Manager/ResourceManager.h"

Bullet::Bullet(const glm::vec2& position, const glm::vec2& size,
         const glm::vec2& direction, float layer,
         IDynamicGameObject::EOrientation orientation, float maxSpeed, int lives)
         : IDynamicGameObject(position, size, glm::normalize(direction), layer)
         , m_lives(lives)
{
    m_maxSpeed = maxSpeed;
    m_currentSpeed = m_maxSpeed;
    m_orientation = orientation;
    m_type = IDynamicGameObject::EDynamicType::Bullet;
    switch(m_orientation)
    {
        case IDynamicGameObject::EOrientation::Top:
            m_pMoveSprite = ResourceManager::getSprite("topBullet8x8");
            m_velocity.y = m_currentSpeed;
            break;
        case IDynamicGameObject::EOrientation::Bottom:
            m_pMoveSprite = ResourceManager::getSprite("bottomBullet8x8");
            m_velocity.y = m_currentSpeed;
            break;
        case IDynamicGameObject::EOrientation::Left:
            m_pMoveSprite = ResourceManager::getSprite("leftBullet8x8");
            m_velocity.x = m_currentSpeed;
            break;
        case IDynamicGameObject::EOrientation::Right:
            m_pMoveSprite = ResourceManager::getSprite("rightBullet8x8");
            m_velocity.x = m_currentSpeed;
            break;
    }
}

void Bullet::render() const
{
    m_pMoveSprite->render(m_position, m_size, m_layer);
}

void Bullet::update(double deltaTime)
{
}
