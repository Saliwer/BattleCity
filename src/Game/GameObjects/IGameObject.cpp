#include "IGameObject.h"

IGameObject::IGameObject(const glm::vec2& position, const glm::vec2& size, float layer) :
                         m_position(position), m_size(size), m_layer(layer)
{}

IDynamicGameObject::IDynamicGameObject(const glm::vec2& position, const glm::vec2& size,
                                       const glm::vec2& direction, float velocity,
                                       float layer)
                                       : IGameObject(position, size, layer)
                                       , m_direction(direction)
                                       , m_velocity(velocity)
{}

IStaticGameObject::IStaticGameObject(const glm::vec2& position, const glm::vec2& size,
                                     float layer)
                                     : IGameObject(position, size, layer)
{}
