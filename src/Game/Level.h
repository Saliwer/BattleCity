#pragma once

#include <vector>
#include <set>
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
public:
    static constexpr unsigned int m_BLOCK_SIZE = 16;

    virtual ~Level(){}
    virtual void render() const;
    virtual void update(uint64_t delta);
    virtual const glm::ivec2& getEnemyRespawnSpot();

    size_t getLevelWidth() const { return (m_width+3) * m_BLOCK_SIZE; }
    size_t getLevelHeight() const { return (m_height+1) * m_BLOCK_SIZE; }
    const glm::ivec2& getPlayer1RespawnSpot() const { return m_playerRespawnSpot_1; }
    const glm::ivec2& getPlayer2RespawnSpot() const { return m_playerRespawnSpot_2; }
    bool isEnemyRespawnSpotAvailable() const { return m_activeRespawnSpots < m_countOfRespawnSpots; }
protected:
    Level(const std::vector<std::string>& levelDescription,
          size_t countOfRespawnSpots);
protected:
    std::vector<std::shared_ptr<IGameObject>>   m_levelObjects;
    size_t                                      m_width;
    size_t                                      m_height;
    glm::ivec2                                  m_playerRespawnSpot_1;
    glm::ivec2                                  m_playerRespawnSpot_2;

    std::vector<glm::ivec2>                     m_enemyRespawnSpots;
    std::set<size_t>                            m_engagedRespawnSpots;
    size_t                                      m_countOfRespawnSpots;
    size_t                                      m_activeRespawnSpots;
};

class EasyLevel : public Level
{
public:
    EasyLevel(const std::vector<std::string>& levelDescription, size_t countOfRespawnSpots);

};
