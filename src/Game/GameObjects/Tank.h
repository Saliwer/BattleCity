#pragma once

#include <glm/vec2.hpp>
#include <glm/glm.hpp>
#include <memory>
#include <list>

#include "IGameObject.h"
#include "../../System/Timer.h"

namespace RenderEngine
{
    class AnimatedSprite;
}
class Bullet;


class Tank : public IDynamicGameObject
{
public:
    Tank(const glm::vec2& position, const glm::vec2& size,
         const glm::vec2& direction, float layer = 0.f);

    virtual void render() const override;
    virtual void update(double deltaTime) override;
    void fire();

    bool isSpawning() const { return m_isSpawning; }

    virtual void setOrientation(EOrientation orientation) override;

private:
    std::shared_ptr<RenderEngine::AnimatedSprite>   m_pMoveSprite;

    std::shared_ptr<RenderEngine::AnimatedSprite>   m_pRespawnSprite;
    std::shared_ptr<RenderEngine::AnimatedSprite>   m_pShieldSprite;

    Timer                                           m_respawnTimer;
    Timer                                           m_shieldTimer;
    bool                                            m_isSpawning;
    bool                                            m_hasShield;
    std::list<std::shared_ptr<Bullet>>              m_bullets;
    double                                          m_reloadingTime;
    bool                                            m_isReloaded;
    Timer                                           m_reloadingTimer;

};
