#pragma once

#include <glm/vec2.hpp>

class IGameObject
{
protected:
    glm::vec2   m_position;
    glm::vec2   m_size;
    glm::vec2   m_direction;
public:
    IGameObject(const glm::vec2& position, const glm::vec2& size, const glm::vec2& direction);
    virtual ~IGameObject();
    virtual void render() const = 0;
    virtual void update(uint64_t delta) = 0;
};
