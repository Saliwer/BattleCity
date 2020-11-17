#include "Level.h"

#include "GameObjects/BrickWall.h"
#include "GameObjects/BetonWall.h"
#include "GameObjects/Tree.h"
#include "GameObjects/Ice.h"
#include "GameObjects/Water.h"
#include "GameObjects/Eagle.h"
#include "GameObjects/Border.h"

#include <iostream>
#include <algorithm>



std::shared_ptr<IStaticGameObject> createGameObject(Level::EGameObjects description,
                                                    const glm::vec2& position)
{
    const glm::vec2 size = glm::vec2(Level::m_BLOCK_SIZE, Level::m_BLOCK_SIZE);

    switch (description) {
    case Level::EGameObjects::brick:
        return std::make_shared<BrickWall>(BrickWall::EBrickWallState::fullBrick, position, size);
    case Level::EGameObjects::water:
        return std::make_shared<BetonWall>(BetonWall::EBetonWallState::Unbroken, position, size);
    case Level::EGameObjects::beton:
        return std::make_shared<Water>(position, size);
    case Level::EGameObjects::tree:
        return std::make_shared<Tree>(position, size, -1.f);
    case Level::EGameObjects::ice:
        return std::make_shared<Ice>(position, size, 1.f);
    case Level::EGameObjects::border:
        return std::make_shared<Border>(position, size, 1.f);
    case Level::EGameObjects::eagle:
        return std::make_shared<Eagle>(true, position, size + glm::vec2(Level::m_BLOCK_SIZE, Level::m_BLOCK_SIZE));
    case Level::EGameObjects::nothing:
        return nullptr;
    default:
        std::cerr << "Unknown object description '" << static_cast<uint8_t>(description) <<
                     "'.\n";
        break;
    }
    return nullptr;
}


LevelDescription::LevelDescription() : ID(0), width(0), height(0)
{}

LevelDescription::LevelDescription(size_t _ID, size_t _width, size_t _height, std::vector<uint8_t> _objects)
                                  : ID(_ID), width(_width), height(_height), objects(std::move(_objects))
{}

LevelDescription::LevelDescription(LevelDescription&& other) noexcept
{
    ID = other.ID;
    width = other.width;
    height = other.height;
    objects = std::move(other.objects);
    other.ID = 0;
    other.width = 0;
    other.height = 0;
}

LevelDescription& LevelDescription::operator=(LevelDescription&& other) noexcept
{
    ID = other.ID;
    width = other.width;
    height = other.height;
    objects = std::move(other.objects);
    other.ID = 0;
    other.width = 0;
    other.height = 0;
    return *this;
}



Level::Level(const LevelDescription& levelDescription,
             size_t countOfRespawnSpots) : m_countOfRespawnSpots(countOfRespawnSpots)
                                         , m_activeRespawnSpots(0)
{
    if (levelDescription.objects.empty())
    {
        std::cerr << "Couldn't create level! Empty level description!\n";
        return;
    }

    m_blocksWidth = levelDescription.width;
    m_blocksHeight = levelDescription.height;
    if (levelDescription.objects.size() != (m_blocksWidth * m_blocksHeight))
    {
        std::cerr << "Count of objects in level description are incorrect!\n";
        return;
    }
    m_pixelWidth = m_blocksWidth * m_BLOCK_SIZE;
    m_pixelHeight = m_blocksHeight * m_BLOCK_SIZE;
    m_staticLevelObjects.reserve(m_blocksWidth * m_blocksHeight);
    for (int row = (int)m_blocksHeight - 1, i = 0; row >= 0; --row, ++i)
    {
        glm::vec2 position;
        position.x = 0.f;
        position.y = static_cast<float>(i * m_BLOCK_SIZE);
        for(int column = 0; column < (int)m_blocksWidth; ++column, position.x+=m_BLOCK_SIZE)
        {
            int index = row * m_blocksWidth + column;
            uint8_t value = levelDescription.objects[index];
            EGameObjects description = static_cast<EGameObjects>(value);
            if (description == EGameObjects::nothing || description == EGameObjects::border)
                continue;
            m_staticLevelObjects.push_back(createGameObject(description,
                                                               position));
        }
    }
    //bottom border
    glm::vec2 position, size;
    position.x = 0.f;
    position.y = 0.f;
    size.x = static_cast<float>(m_pixelWidth);
    size.y = static_cast<float>(2 * m_BLOCK_SIZE);
    m_staticLevelObjects.push_back(std::make_shared<Border>(position, size, 1.f));
    //left border
    position.x = 0.f;
    position.y = static_cast<float>(2 * m_BLOCK_SIZE);
    size.x = static_cast<float>(2 * m_BLOCK_SIZE);
    size.y = static_cast<float>(m_pixelHeight - 4 * m_BLOCK_SIZE);
    m_staticLevelObjects.push_back(std::make_shared<Border>(position, size, 1.f));
    //top border
    position.x = 0.f;
    position.y = static_cast<float>(m_pixelHeight - 2 * m_BLOCK_SIZE);
    size.x = static_cast<float>(m_pixelWidth);
    size.y = static_cast<float>(2 * m_BLOCK_SIZE);
    m_staticLevelObjects.push_back(std::make_shared<Border>(position, size, 1.f));
    //right borer
    position.x = static_cast<float>(m_pixelWidth - 4 * m_BLOCK_SIZE);
    position.y = static_cast<float>(2 * m_BLOCK_SIZE);
    size.x = static_cast<float>(4 * m_BLOCK_SIZE);
    size.y = static_cast<float>(m_pixelHeight - 4 * m_BLOCK_SIZE);
    m_staticLevelObjects.push_back(std::make_shared<Border>(position, size, 1.f));

    m_playerRespawnSpot_1 = glm::ivec2(22 * m_BLOCK_SIZE, 61 * m_BLOCK_SIZE);
    m_playerRespawnSpot_2 = glm::ivec2(33 * m_BLOCK_SIZE, 61 * m_BLOCK_SIZE);
}


void Level::render() const
{
    for (const auto& object : m_staticLevelObjects)
            object->render();
}

void Level::update(double delta)
{
    for (const auto& object : m_staticLevelObjects)
        if (object)
            object->update(delta);
}

const glm::ivec2& Level::getEnemyRespawnSpot()
{
    do
    {
        size_t index = rand() % m_enemyRespawnSpots.size();
        auto searchIt = m_engagedRespawnSpots.find(index);
        if (searchIt != m_engagedRespawnSpots.end())
            continue;
        else{
            m_engagedRespawnSpots.insert(index);
            ++m_activeRespawnSpots;
            return m_enemyRespawnSpots[index];
        }
    }while(true);
}

std::vector<std::shared_ptr<IStaticGameObject>>
Level::getObjectsInArea(const glm::vec2& leftBottomXY,
                        const glm::vec2& rightTopXY)
{
    float levelWidth = (float)getLevelWidth();
    float levelHeight = (float)getLevelHeight();

    float xConverted = std::clamp(leftBottomXY.x - m_BLOCK_SIZE, 0.f, levelWidth);
    float yConverted = std::clamp(levelHeight - leftBottomXY.y - m_BLOCK_SIZE /2.f, 0.f, levelHeight);
    glm::vec2 convertedLeftBottomXY = glm::vec2(xConverted, yConverted);

    xConverted = std::clamp(rightTopXY.x - m_BLOCK_SIZE, 0.f, levelWidth);
    yConverted = std::clamp(levelHeight - rightTopXY.y - m_BLOCK_SIZE/2.f, 0.f, levelHeight);
    glm::vec2 convertedRightTopXY = glm::vec2(xConverted, yConverted);

    const uint8_t maxIntersectedObjects = 4;
    std::vector<std::shared_ptr<IStaticGameObject>> output;

    size_t startX = static_cast<size_t>(convertedLeftBottomXY.x / m_BLOCK_SIZE);
    size_t endX = static_cast<size_t>(convertedRightTopXY.x / m_BLOCK_SIZE);

    size_t startY = static_cast<size_t>(convertedRightTopXY.y / m_BLOCK_SIZE);
    size_t endY = static_cast<size_t>(convertedLeftBottomXY.y / m_BLOCK_SIZE);

    std::cout << "startX = " << startX << "\t endX = " << endX << std::endl;
    std::cout << "startY = " << startY << "\t endY = " << endY << std::endl;

    for (size_t currentRow = startX; startX <= endX; ++startX)
    {
        for (size_t currentColumn = startY; startY <= endY; ++startY)
        {
            std::shared_ptr<IStaticGameObject> object = m_staticLevelObjects[currentRow * m_blocksWidth + currentColumn];
            if (object)
                output.push_back(object);
        }
    }

    std::cout << "output.size() = " << output.size() << std::endl;


    return output;
}

EasyLevel::EasyLevel(const LevelDescription& levelDescription) : Level(levelDescription, 3)
{
    /*m_enemyRespawnSpots.reserve(m_countOfRespawnSpots);
    unsigned int YOffset = m_BLOCK_SIZE * (m_blocksHeight - 1) + m_BLOCK_SIZE / 2.f;
    unsigned int XOffset = m_BLOCK_SIZE;

    const std::string& firstRow = levelDescription[0];
    for (const char& currentDescription : firstRow)
    {
        if (currentDescription=='D' || currentDescription=='B' || currentDescription=='C')
            m_enemyRespawnSpots.push_back(glm::ivec2(XOffset, YOffset));
        XOffset += m_BLOCK_SIZE;
    }*/
}


