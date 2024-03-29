#pragma once

#include <glm/vec2.hpp>
#include <glm/glm.hpp>
#include <memory>

#include "IGameObject.h"
#include "../../System/Timer.h"

namespace RenderEngine
{
    class Sprite;
    class AnimatedSprite;
}

class Bullet : public IDynamicGameObject
{
public:
    Bullet(const glm::vec2& position, const glm::vec2& size,
         const glm::vec2& direction, float layer,
         IDynamicGameObject::EOrientation orientation, float maxSpeed, int lives = 1);

    virtual void render() const override;
    virtual void update(double deltaTime) override;
    void blowUp();
private:
    std::shared_ptr<RenderEngine::Sprite>           m_pMoveSprite;
    int                                             m_lives;
    std::shared_ptr<RenderEngine::AnimatedSprite>   m_pExplosionSprite;
    Timer                                           m_explodeTime;
    bool                                            m_isExploding;
    glm::vec2                                       m_explosionOffset;
    static double                                   explosionTime;

};
