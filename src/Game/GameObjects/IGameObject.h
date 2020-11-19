#pragma once

#include <glm/vec2.hpp>
#include <glm/glm.hpp>
#include <vector>
#include "../../Physics/PhysicsEngine.h"

class Tank;
class Bullet;

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
    const Physics::AABB& getGlobalAABB() const { return m_AABB; }

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
    enum class EOrientation
    {
        Top,
        Bottom,
        Left,
        Right
    };

    enum class EDynamicType
    {
        TankType1,
        Bullet
    };

    IDynamicGameObject(const glm::vec2& position, const glm::vec2& size,
                       const glm::vec2& direction, float layer = 0.f);

    virtual ~IDynamicGameObject() {}

    virtual Physics::AABB& getGlobalAABB() override;
    const glm::vec2& getDirection() const { return m_direction; }
    glm::vec2& getVelocity() { return m_velocity; }
    float getMaxSpeed() const { return m_maxSpeed; }
    float getCurrentSpeed() const { return m_currentSpeed; }
    float getSlideSmooth() const { return m_slideSmooth; }
    float getNormalSmooth() const { return m_normalSmooth; }
    float getCurrentSmooth() const { return m_currentSmooth; }
    EDynamicType getType() const { return m_type; }

    bool isSliding() const { return (m_velocity.x != m_maxSpeed) && (m_velocity.y != m_maxSpeed); }
    bool isMoving() const { return (m_velocity.x > 1.f || m_velocity.y > 1.f); }
    bool isAlive() const { return m_isAlive; }

    void setVelocity(const glm::vec2& velocity) { m_velocity = velocity; }
    void setDirection(const glm::vec2& direction) { m_direction = glm::normalize(direction); }
    void setSpeed(float value) { m_currentSpeed = value; }
    void setCurrentSmooth(float smoothValue) { m_currentSmooth = smoothValue; }
    void setLive(bool live) { m_isAlive = live; }

    virtual void setOrientation(EOrientation orientation) { m_orientation = orientation; };
    // TODO override collision for dynamic objects
    //virtual bool checkCollision(std::shared_ptr<IDynamicGameObject>) = 0;

protected:
    glm::vec2       m_direction;
    glm::vec2       m_velocity;
    float           m_maxSpeed;
    float           m_currentSpeed;
    float           m_slideSmooth;      //TODO - transfer to Tank interface
    float           m_normalSmooth;     //TODO - transfer to Tank interface
    float           m_currentSmooth;    //TODO - transfer to Tank interface
    bool            m_isAlive;
    EOrientation    m_orientation;
    EDynamicType    m_type;
};

class IStaticGameObject : public IGameObject
{
public:
    IStaticGameObject(const glm::vec2& position, const glm::vec2& size, float layer = 0.f);

    virtual ~IStaticGameObject() {}

    virtual void update(double delta) override {}

    virtual bool checkCollision(std::shared_ptr<IDynamicGameObject> dynObject,
                                const glm::vec2& newPosition) = 0;

protected:
    virtual void handlingCollision(Tank* tank) = 0;
    virtual void handlingCollision(Bullet* bullet) = 0;
};
