#pragma once

#include <glm/vec2.hpp>
#include <memory>

namespace RenderEngine
{
    class AnimatedSprite;
}

class Tank
{
    std::shared_ptr<RenderEngine::AnimatedSprite> m_pSprite;
    glm::vec2 m_position;
    glm::vec2 m_velocity;
    bool m_move;
    glm::vec2 m_direction;
public:
    Tank(std::shared_ptr<RenderEngine::AnimatedSprite> pSprite, const glm::vec2& position, float velocity);

    void render() const;
    void update(uint64_t deltaTime);
    void setSpriteState(const std::string& state);

    void move(bool move) { m_move = move; }
    void setPosition(const glm::vec2& position) { m_position = position; }
    void setVelocity(float velocity) { m_velocity = glm::vec2(velocity, velocity); }
    void setDirection(const glm::vec2& direction) { m_direction = direction; }

    const glm::vec2& getVelocity() const { return m_velocity; }
    const glm::vec2& getPosition() const { return m_position; }
    const glm::vec2& getDirection() const { return m_direction; }
};
