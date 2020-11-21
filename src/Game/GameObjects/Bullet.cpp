#include "Bullet.h"
#include "../../Renderer/Sprite.h"
#include "../../Renderer/AnimatedSprite.h"
#include "../../Manager/ResourceManager.h"

double Bullet::explosionTime = 450.0;

Bullet::Bullet(const glm::vec2& position, const glm::vec2& size,
         const glm::vec2& direction, float layer,
         IDynamicGameObject::EOrientation orientation, float maxSpeed, int lives)
         : IDynamicGameObject(position, size, glm::normalize(direction), layer)
         , m_lives(lives), m_isExploding(false)
{
    m_maxSpeed = maxSpeed;
    m_currentSpeed = m_maxSpeed;
    m_orientation = orientation;
    m_type = IDynamicGameObject::EDynamicType::Bullet;
    m_explodeTime.setCallBack([this]()
                              {
                                  if (--m_lives <= 0)
                                    m_isAlive = false;
                                  m_isExploding = false;
                              });
    switch(m_orientation)
    {
        case IDynamicGameObject::EOrientation::Top:
            m_pMoveSprite = ResourceManager::getSprite("topBullet8x8");
            m_velocity.y = m_currentSpeed;
            m_explosionOffset = glm::vec2(-4.f, 0.f);
            break;
        case IDynamicGameObject::EOrientation::Bottom:
            m_pMoveSprite = ResourceManager::getSprite("bottomBullet8x8");
            m_velocity.y = m_currentSpeed;
            m_explosionOffset = glm::vec2(-4.f, -8.f);
            break;
        case IDynamicGameObject::EOrientation::Left:
            m_pMoveSprite = ResourceManager::getSprite("leftBullet8x8");
            m_velocity.x = m_currentSpeed;
            m_explosionOffset = glm::vec2(-8.f, -4.f);
            break;
        case IDynamicGameObject::EOrientation::Right:
            m_pMoveSprite = ResourceManager::getSprite("rightBullet8x8");
            m_velocity.x = m_currentSpeed;
            m_explosionOffset = glm::vec2(0.f, -4.f);
            break;
    }
    m_pExplosionSprite = ResourceManager::getAnimatedSprite("explosion");
}

void Bullet::render() const
{
    if (m_isExploding)
        m_pExplosionSprite->render(m_position + m_explosionOffset, 2.f*m_size, m_layer);
    else
        m_pMoveSprite->render(m_position, m_size, m_layer);
}

void Bullet::update(double deltaTime)
{
    if (m_isExploding)
    {
        m_pExplosionSprite->update(deltaTime);
        m_explodeTime.update(deltaTime);
    }
}

void Bullet::blowUp()
{
    m_isExploding = true;
    m_explodeTime.start(Bullet::explosionTime);
}
