#pragma once

#include <glm/vec2.hpp>
#include <glm/glm.hpp>
#include <memory>

#include "IGameObject.h"
#include "../../System/Timer.h"

namespace RenderEngine
{
    class AnimatedSprite;
}



class Tank : public IDynamicGameObject
{
public:
    Tank(const glm::vec2& position, const glm::vec2& size,
         const glm::vec2& direction, float layer = 0.f);

    virtual void render() const override;
    virtual void update(double deltaTime) override;

    bool isSpawning() const { return m_isSpawning; }

    float getMaxSpeed() const { return m_maxSpeed; }
    virtual Physics::AABB& getGlobalAABB() override;

    void setSprite(std::shared_ptr<RenderEngine::AnimatedSprite> pMoveSprite);

private:
    std::shared_ptr<RenderEngine::AnimatedSprite>   m_pMoveSprite;
    const float                                     m_maxSpeed;

    std::shared_ptr<RenderEngine::AnimatedSprite>   m_pRespawnSprite;
    std::shared_ptr<RenderEngine::AnimatedSprite>   m_pShieldSprite;

    Timer                                           m_respawnTimer;
    Timer                                           m_shieldTimer;
    bool                                            m_isSpawning;
    bool                                            m_hasShield;

};
