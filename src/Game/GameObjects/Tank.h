#pragma once

#include <glm/vec2.hpp>
#include <glm/glm.hpp>
#include <memory>
#include "IGameObject.h"

namespace RenderEngine
{
    class AnimatedSprite;
}


class Tank : public IGameObject
{
public:
    Tank(const glm::vec2& position, const glm::vec2& size,
         const glm::vec2& direction, float velocity, float layer = 0.f);

    virtual void render() const override;
    virtual void update(uint64_t deltaTime) override;

    void move(bool move) { m_move = move; }
    void setPosition(const glm::vec2& position) { m_position = position; }
    void setVelocity(float velocity) { m_velocity = glm::vec2(velocity, velocity); }
    void setDirection(const glm::vec2& direction) { m_direction = glm::normalize(direction); }
    void setSize(const glm::vec2& size) { m_size = size; }

    const glm::vec2& getVelocity() const { return m_velocity; }
    const glm::vec2& getSize() const {return m_size; }
    const glm::vec2& getPosition() const { return m_position; }
    const glm::vec2& getDirection() const { return m_direction; }

private:
    std::shared_ptr<RenderEngine::AnimatedSprite> m_pMoveSprite;
    glm::vec2 m_velocity;
    bool m_move;
};
