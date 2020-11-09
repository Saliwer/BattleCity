#pragma once

#include "IGameObject.h"

#include <memory>
#include <array>

namespace RenderEngine {
    class Sprite;
}

class Eagle : public IGameObject
{
public:
    Eagle(bool isAlive, const glm::vec2& position, const glm::vec2& size,
          const glm::vec2& direction, float layer = 0.f);
    virtual ~Eagle();
    virtual void render() const override;
    virtual void update(uint64_t delta) override {}
    bool isAlive() const { return m_isAlive; }
    void setLive(bool live) { m_isAlive = live; }
private:
    std::shared_ptr<RenderEngine::Sprite>  m_pAliveSprite;
    std::shared_ptr<RenderEngine::Sprite>  m_pDeadSprite;
    bool                                   m_isAlive;
};
