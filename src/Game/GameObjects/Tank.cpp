#include "Tank.h"

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
           , m_isSpawning(true), m_hasShield(false)
{
    m_slideSmooth = 0.95f;
    m_normalSmooth = 0.85f;
    m_currentSmooth = m_normalSmooth;
    m_maxSpeed = 60.f;
    m_currentSpeed = m_maxSpeed;
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

    m_AABB.leftBottomXY = m_position;
    m_AABB.rightTopXY = m_position + m_size;
}

void Tank::setSprite(std::shared_ptr<RenderEngine::AnimatedSprite> pMoveSprite)
{
    m_pMoveSprite = std::move(pMoveSprite);
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
        if (m_move)
        {
            m_pMoveSprite->update(deltaTime);
        }
        if (m_hasShield)
        {
            m_pShieldSprite->update(deltaTime);
            m_shieldTimer.update(deltaTime);
        }
    }
}

Physics::AABB& Tank::getGlobalAABB()
{
    m_AABB.leftBottomXY = m_position;
    m_AABB.rightTopXY = m_position + m_size;
    return m_AABB;
}

