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
    virtual Physics::AABB& getGlobalAABB() { return m_AABB; }
    virtual const Physics::AABB& getGlobalAABB() const { return m_AABB; }

    const glm::vec2& getSize() const { return m_size; }
    float getLayer() const { return m_layer; }

    void setPosition(const glm::vec2& position) { m_position = position; }
    void setSize(const glm::vec2& size) { m_size = size; }

protected:
    bool hasIntersection(const Physics::AABB& objAABB) const;

protected:
    glm::vec2       m_position;
    glm::vec2       m_size;
    float           m_layer;
    Physics::AABB   m_AABB;
};

class IDynamicGameObject : public IGameObject
{
public:
    IDynamicGameObject(const glm::vec2& position, const glm::vec2& size,
                       const glm::vec2& direction, float layer = 0.f);

    virtual ~IDynamicGameObject() {}

    const glm::vec2& getDirection() const { return m_direction; }
    glm::vec2& getVelocity() { return m_velocity; }
    float getMaxSpeed() const { return m_maxSpeed; }
    float getCurrentSpeed() const { return m_currentSpeed; }
    float getSlideSmooth() const { return m_slideSmooth; }
    float getNormalSmooth() const { return m_normalSmooth; }
    float getCurrentSmooth() const { return m_currentSmooth; }
    bool isMoving() const { return m_move; }
    bool isSliding() const { return (m_velocity.x > 1e-5 || m_velocity.y > 1e-5); }


    void setVelocity(const glm::vec2& velocity) { m_velocity = velocity; }
    void setDirection(const glm::vec2& direction) { m_direction = glm::normalize(direction); }
    void setSpeed(float value) { m_currentSpeed = value; }
    void move(bool flag) { m_move = flag; }
    void setCurrentSmooth(float smoothValue) { m_currentSmooth = smoothValue; }
    // TODO override collision for dynamic objects
    //virtual bool checkCollision(std::shared_ptr<IDynamicGameObject>) = 0;

protected:
    glm::vec2       m_direction;
    glm::vec2       m_velocity;
    float           m_maxSpeed;
    float           m_currentSpeed;
    bool            m_move;
    float           m_slideSmooth;
    float           m_normalSmooth;
    float           m_currentSmooth;

};

class IStaticGameObject : public IGameObject
{
public:
    IStaticGameObject(const glm::vec2& position, const glm::vec2& size, float layer = 0.f);

    virtual ~IStaticGameObject() {}

    virtual void update(double delta) override {}

    virtual bool checkCollision(std::shared_ptr<IDynamicGameObject>, const glm::vec2&){ return false; }
};
