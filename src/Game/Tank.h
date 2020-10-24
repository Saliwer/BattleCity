#pragma once

#include <glm/vec2.hpp>
#include <memory>

namespace Renderer
{
    class AnimatedSprite;
}

class Tank
{
    std::shared_ptr<Renderer::AnimatedSprite> m_pSprite;
    glm::vec2 m_position;
    float m_velocity;
    bool m_move;
    glm::vec2 m_direction;
public:
    Tank(std::shared_ptr<Renderer::AnimatedSprite> pSprite, const glm::vec2& position, float velocity);

    void render() const;
    void update(uint64_t deltaTime);
    void setSpriteState(const std::string& state);

    void move(bool move) { m_move = move; }
    void setPosition(const glm::vec2& position) { m_position = position; }
    void setVelocity(float velocity) { m_velocity = velocity; }
    void setDirection(const glm::vec2& direction) { m_direction = direction; }

    float getVelocity() const { return m_velocity; }
    const glm::vec2& getPosition() const { return m_position; }
    const glm::vec2& getDirection() const { return m_direction; }
};
