#pragma once

#include <glm/vec2.hpp>
#include <glm/glm.hpp>
#include <vector>
#include "../../Physics/PhysicsEngine.h"

class IGameObject
{
public:
    IGameObject(const glm::vec2& position, const glm::vec2& size, float layer = 0.f);

    virtual ~IGameObject() {}

    virtual void render() const = 0;
    virtual void update(double delta) = 0;

    const glm::vec2& getPosition() const { return m_position; }
    glm::vec2& getPosition() { return m_position; }
    const glm::vec2& getSize() const { return m_size; }
    float getLayer() const { return m_layer; }

    void setPosition(const glm::vec2& position) { m_position = position; }
    void setSize(const glm::vec2& size) { m_size = size; }

protected:
    glm::vec2   m_position;
    glm::vec2   m_size;
    float       m_layer;
};

class IDynamicGameObject : public IGameObject
{
public:
    IDynamicGameObject(const glm::vec2& position, const glm::vec2& size,
                       const glm::vec2& direction, float velocity, float layer = 0.f);

    virtual ~IDynamicGameObject() {}

    const glm::vec2& getDirection() const { return m_direction; }
    float getVelocity() const { return m_velocity; }
    virtual Physics::AABB& getGlobalAABB() { return m_AABB; }

    virtual void setVelocity(float velocity) { m_velocity = velocity; }
    void setDirection(const glm::vec2& direction) { m_direction = glm::normalize(direction); }

protected:
    glm::vec2       m_direction;
    float           m_velocity;
    Physics::AABB   m_AABB;
};

class IStaticGameObject : public IGameObject
{
public:
    IStaticGameObject(const glm::vec2& position, const glm::vec2& size, float layer = 0.f);

    virtual ~IStaticGameObject() {}

    virtual std::vector<Physics::AABB>& getGlobalAABB() { return m_AABBs; }

    virtual void update(double delta) override {}
protected:
    std::vector<Physics::AABB> m_AABBs;
};
