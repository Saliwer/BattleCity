#pragma once

#include <vector>
#include <memory>
#include <string>
#include <glm/vec2.hpp>
class IGameObject;

std::shared_ptr<IGameObject>
createGameObjectFromChar(const char description,
                         const glm::vec2& position,
                         const glm::vec2& size,
                         const glm::vec2& direction);

class Level
{
    std::vector<std::shared_ptr<IGameObject>> m_levelObjects;
    size_t m_width;
    size_t m_height;

public:
    static constexpr unsigned int m_BLOCK_SIZE = 16;

    Level(const std::vector<std::string>& levelDescription);
    void render() const;
    void update(uint64_t delta);
    size_t getLevelWidth() const { return (m_width+3) * m_BLOCK_SIZE; }
    size_t getLevelHeight() const { return (m_height+1) * m_BLOCK_SIZE; }
};
