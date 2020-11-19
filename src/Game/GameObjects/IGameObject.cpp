#include "IGameObject.h"

IGameObject::IGameObject(const glm::vec2& position, const glm::vec2& size, float layer) :
                         m_position(position), m_size(size), m_layer(layer)
{
    m_AABB.leftBottomXY = m_position;
    m_AABB.rightTopXY = m_position + m_size;
}

bool IGameObject::hasIntersection(const Physics::AABB& objAABB) const
{
    // 2 demension
    for (size_t i = 0; i < 2; ++i)
    {
        if (m_AABB.leftBottomXY[i] > objAABB.rightTopXY[i])
            return false;
        if (m_AABB.rightTopXY[i] < objAABB.leftBottomXY[i])
            return false;
    }
    return true;
}

IDynamicGameObject::IDynamicGameObject(const glm::vec2& position, const glm::vec2& size,
                                       const glm::vec2& direction, float layer)
                                       : IGameObject(position, size, layer)
                                       , m_direction(direction)
                                       , m_velocity(0.f, 0.f)
                                       , m_isAlive(true)
{}

Physics::AABB& IDynamicGameObject::getGlobalAABB()
{
    m_AABB.leftBottomXY = m_position;
    m_AABB.rightTopXY = m_position + m_size;
    return m_AABB;
}



IStaticGameObject::IStaticGameObject(const glm::vec2& position, const glm::vec2& size,
                                     float layer)
                                     : IGameObject(position, size, layer)
{}
