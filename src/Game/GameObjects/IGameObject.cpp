#include "IGameObject.h"

IGameObject::IGameObject(const glm::vec2& position, const glm::vec2& size,
                         const glm::vec2& direction, float layer) :
                         m_position(position), m_size(size),
                         m_direction(direction), m_layer(layer)
{}

IGameObject::~IGameObject()
{}
