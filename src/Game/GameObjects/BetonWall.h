#pragma once

#include "IGameObject.h"

#include <memory>

namespace RenderEngine {
    class Sprite;
}

class BetonWall : public IStaticGameObject
{
public:

    enum class EBetonWallState : uint8_t
    {
        Unbroken,
        Destroyed
    };

    BetonWall(EBetonWallState betonWallState,
              const glm::vec2& position, const glm::vec2& size, float layer = 0);
    virtual ~BetonWall();
    virtual void render() const override;

private:
    EBetonWallState                         m_eCurrentBetonState;
    std::shared_ptr<RenderEngine::Sprite>   m_pSprite;
};
