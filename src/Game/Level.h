#pragma once

#include <vector>
#include <unordered_set>
#include <memory>
#include <string>
#include <glm/vec2.hpp>
class IStaticGameObject;

struct LevelDescription
{
    LevelDescription();
    LevelDescription(size_t _ID, size_t _width, size_t _height, std::vector<uint8_t> _objects);
    LevelDescription(LevelDescription&& other) noexcept;
    LevelDescription& operator=(LevelDescription&& other) noexcept;

    LevelDescription(const LevelDescription& other) = delete;
    LevelDescription& operator=(LevelDescription& other) = delete;

    size_t                  ID;
    size_t                  width;
    size_t                  height;
    std::vector<uint8_t>    objects;
};

class Level
{
public:
    enum class EGameObjects : uint8_t
    {
        nothing = 0,
        brick   = 1,
        water   = 16,
        beton   = 19,
        tree    = 20,
        ice     = 21,
        border  = 22,
        eagle   = 31
    };

    static constexpr unsigned int m_BLOCK_SIZE = 8;

    virtual ~Level(){}
    virtual void render() const;
    virtual void update(double delta);
    virtual const glm::ivec2& getEnemyRespawnSpot();

    size_t getLevelWidth() const { return (m_blocksWidth+3) * m_BLOCK_SIZE; }
    size_t getLevelHeight() const { return (m_blocksHeight+1) * m_BLOCK_SIZE; }
    const glm::ivec2& getPlayer1RespawnSpot() const { return m_playerRespawnSpot_1; }
    const glm::ivec2& getPlayer2RespawnSpot() const { return m_playerRespawnSpot_2; }
    bool isEnemyRespawnSpotAvailable() const { return m_activeRespawnSpots < m_countOfRespawnSpots; }

    std::vector<std::shared_ptr<IStaticGameObject>> getObjectsInArea(const glm::vec2& leftBottomXY,
                                                                     const glm::vec2& rightTopXY);
protected:
    Level(const LevelDescription& levelDescription,
          size_t countOfRespawnSpots);
protected:
    std::vector<std::shared_ptr<IStaticGameObject>> m_staticLevelObjects;
    size_t                                          m_blocksWidth;
    size_t                                          m_blocksHeight;
    size_t                                          m_pixelWidth;
    size_t                                          m_pixelHeight;
    glm::ivec2                                      m_playerRespawnSpot_1;
    glm::ivec2                                      m_playerRespawnSpot_2;

    std::vector<glm::ivec2>                         m_enemyRespawnSpots;
    std::unordered_set<size_t>                      m_engagedRespawnSpots;
    size_t                                          m_countOfRespawnSpots;
    size_t                                          m_activeRespawnSpots;
};

class EasyLevel : public Level
{
public:
    EasyLevel(const LevelDescription& levelDescription);
};

std::shared_ptr<IStaticGameObject> createGameObject(Level::EGameObjects description,
                                                    const glm::vec2& position);
