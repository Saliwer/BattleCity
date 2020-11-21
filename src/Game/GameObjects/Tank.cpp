#include "Tank.h"
#include "Bullet.h"
#include "../../Renderer/AnimatedSprite.h"
#include "../../Manager/ResourceManager.h"


#include <iostream>
extern glm::ivec2 g_WindowSize;

Tank::Tank(const glm::vec2& position, const glm::vec2& size,
           const glm::vec2& direction, float layer)
           : IDynamicGameObject(position, size, glm::normalize(direction), layer)
           , m_pMoveSprite(ResourceManager::getAnimatedSprite("tankYellowType1Top"))
           , m_pRespawnSprite(ResourceManager::getAnimatedSprite("respawn"))
           , m_pShieldSprite(ResourceManager::getAnimatedSprite("shield"))
           , m_isSpawning(true), m_hasShield(false), m_isReloaded(true)
{
    m_slideSmooth = 0.95f;
    m_normalSmooth = 0.55f;
    m_currentSmooth = m_normalSmooth;
    m_maxSpeed = 60.f;
    m_currentSpeed = m_maxSpeed;
    m_orientation = IDynamicGameObject::EOrientation::Top;
    m_type = IDynamicGameObject::EDynamicType::TankType1;
    m_respawnTimer.setCallBack([this]()
                               {
                                  m_isSpawning = false;
                                  m_hasShield = true;
                                  m_shieldTimer.start(2000);
                               });
    m_respawnTimer.start(2000);
    m_shieldTimer.setCallBack([this]()
                              {
                                 m_hasShield = false;
                              });
    m_reloadingTime = 1000.0;
    m_reloadingTimer.setCallBack([this]()
                                 {
                                    m_isReloaded = true;
                                 });
}

void Tank::render() const
{
    if (m_isSpawning)
        m_pRespawnSprite->render(m_position, m_size, m_layer);
    else
    {
        if (m_hasShield)
            m_pShieldSprite->render(m_position, m_size, m_layer);
        m_pMoveSprite->render(m_position, m_size, m_layer);
        for(auto& bullet : m_bullets)
            if (bullet)
                bullet->render();
    }

}

void Tank::update(double deltaTime)
{
    if (m_isSpawning)
    {
        m_pRespawnSprite->update(deltaTime);
        m_respawnTimer.update(deltaTime);
    }
    else
    {
        if (isMoving() && !isSliding())
        {
            m_pMoveSprite->update(deltaTime);
        }
        if (m_hasShield)
        {
            m_pShieldSprite->update(deltaTime);
            m_shieldTimer.update(deltaTime);
        }

        for (auto bullet_it = m_bullets.begin(); bullet_it != m_bullets.end(); )
        {
            if ((*bullet_it)->isAlive())
            {
                (*bullet_it)->update(deltaTime);
                ++bullet_it;
            }
            else
                bullet_it = m_bullets.erase(bullet_it);
        }
    }
    if (!m_isReloaded)
        m_reloadingTimer.update(deltaTime);
}

void Tank::setOrientation(EOrientation orientation)
{
    m_orientation = orientation;
    switch(m_orientation)
    {
        case IDynamicGameObject::EOrientation::Top:
            m_direction = glm::vec2(0.f, 1.f);
            m_pMoveSprite = ResourceManager::getAnimatedSprite("tankYellowType1Top");
            m_velocity.y = m_currentSpeed;
            break;
        case IDynamicGameObject::EOrientation::Bottom:
            m_direction = glm::vec2(0.f, -1.f);
            m_pMoveSprite = ResourceManager::getAnimatedSprite("tankYellowType1Bottom");
            m_velocity.y = m_currentSpeed;
            break;
        case IDynamicGameObject::EOrientation::Left:
            m_direction = glm::vec2(-1.f, 0.f);
            m_pMoveSprite = ResourceManager::getAnimatedSprite("tankYellowType1Left");
            m_velocity.x = m_currentSpeed;
            break;
        case IDynamicGameObject::EOrientation::Right:
            m_direction = glm::vec2(1.f, 0.f);
            m_pMoveSprite = ResourceManager::getAnimatedSprite("tankYellowType1Right");
            m_velocity.x = m_currentSpeed;
            break;
    }
}

void Tank::fire()
{
    if (m_isReloaded)
    {
        glm::vec2 bulletPosition = m_position + m_size / 4.f + m_size * m_direction / 4.f;
        m_bullets.emplace_back(std::make_shared<Bullet>(bulletPosition, glm::vec2(8.f, 8.f),
                                                        m_direction, m_layer, m_orientation,
                                                        m_maxSpeed * 2.f));
        Physics::PhysicsEngine::addDynamicObject(m_bullets.back());
        m_reloadingTimer.start(m_reloadingTime);
        m_isReloaded = false;
    }
}
