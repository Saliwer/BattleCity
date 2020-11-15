#include "Level.h"

#include "GameObjects/BrickWall.h"
#include "GameObjects/BetonWall.h"
#include "GameObjects/Tree.h"
#include "GameObjects/Ice.h"
#include "GameObjects/Water.h"
#include "GameObjects/Eagle.h"
#include "GameObjects/Border.h"

#include <iostream>




std::shared_ptr<IStaticGameObject>
createGameObjectFromChar(const char description,
                         const glm::vec2& position,
                         const glm::vec2& size)
{
    switch (description) {
    case '0':
        return std::make_shared<BrickWall>(BrickWall::EBrickWallType::Right, position, size);
    case '1':
        return std::make_shared<BrickWall>(BrickWall::EBrickWallType::Bottom, position, size);
    case '2':
        return std::make_shared<BrickWall>(BrickWall::EBrickWallType::Left, position, size);
    case '3':
        return std::make_shared<BrickWall>(BrickWall::EBrickWallType::Top, position, size);
    case '4':
        return std::make_shared<BrickWall>(BrickWall::EBrickWallType::All, position, size);
    case 'G':
        return std::make_shared<BrickWall>(BrickWall::EBrickWallType::BottomLeft, position, size);
    case 'H':
        return std::make_shared<BrickWall>(BrickWall::EBrickWallType::BottomRight, position, size);
    case 'I':
        return std::make_shared<BrickWall>(BrickWall::EBrickWallType::TopLeft, position, size);
    case 'J':
        return std::make_shared<BrickWall>(BrickWall::EBrickWallType::TopRight, position, size);
    case '5':
        return std::make_shared<BetonWall>(BetonWall::EBetonWallType::Right, position, size);
    case '6':
        return std::make_shared<BetonWall>(BetonWall::EBetonWallType::Bottom, position, size);
    case '7':
        return std::make_shared<BetonWall>(BetonWall::EBetonWallType::Left, position, size);
    case '8':
        return std::make_shared<BetonWall>(BetonWall::EBetonWallType::Top, position, size);
    case '9':
        return std::make_shared<BetonWall>(BetonWall::EBetonWallType::All, position, size);
    case 'A':
        return std::make_shared<Water>(position, size);
    case 'B':
        return std::make_shared<Tree>(position, size, -1.f);
    case 'C':
        return std::make_shared<Ice>(position, size, 1.f);
    case 'E':
        return std::make_shared<Eagle>(true, position, size);
    case 'D':
        return nullptr;
    default:
        std::cerr << "Unknown char description '" << description <<
                     "'.\n";
        break;
    }
    return nullptr;
}


Level::Level(const std::vector<std::string>& levelDescription,
             size_t countOfRespawnSpots) : m_countOfRespawnSpots(countOfRespawnSpots)
                                         , m_activeRespawnSpots(0)
{
    if (levelDescription.empty())
    {
        std::cerr << "Couldn't create level! Empty level description!\n";
        return;
    }

    m_blocksWidth = levelDescription[0].length();
    m_blocksHeight = levelDescription.size();
    const unsigned char countBorders = 4;
    m_staticLevelObjects.reserve(m_blocksWidth * m_blocksHeight + countBorders);
    unsigned int YOffset = m_BLOCK_SIZE * (m_blocksHeight - 1) + m_BLOCK_SIZE / 2.f;
    for (const std::string& currentRow : levelDescription)
    {
        unsigned int XOffset = m_BLOCK_SIZE;
        for (const char currentDescription : currentRow)
        {
            if (currentDescription == 'K')
                m_playerRespawnSpot_1 = glm::ivec2(XOffset, YOffset);
            else if (currentDescription == 'L')
                m_playerRespawnSpot_2 = glm::ivec2(XOffset, YOffset);
            else
                m_staticLevelObjects.emplace_back(createGameObjectFromChar(currentDescription,
                                                                     glm::vec2(XOffset, YOffset),
                                                                     glm::vec2(m_BLOCK_SIZE, m_BLOCK_SIZE)));

            XOffset += m_BLOCK_SIZE;
        }
        YOffset -= m_BLOCK_SIZE;
    }

    //Add borders
    //bottom border
    m_staticLevelObjects.emplace_back(std::make_shared<Border>(glm::vec2(m_BLOCK_SIZE, 0.f),
                                                               glm::vec2(m_blocksWidth*m_BLOCK_SIZE, m_BLOCK_SIZE/2.f)));
    //top border
    m_staticLevelObjects.emplace_back(std::make_shared<Border>(glm::vec2(m_BLOCK_SIZE, m_blocksHeight * m_BLOCK_SIZE + m_BLOCK_SIZE/2.f),
                                                               glm::vec2(m_blocksWidth*m_BLOCK_SIZE, m_BLOCK_SIZE/2.f)));
    //left border
    m_staticLevelObjects.emplace_back(std::make_shared<Border>(glm::vec2(0.f, 0.f),
                                                               glm::vec2(m_BLOCK_SIZE, getLevelHeight())));
    //right border
    m_staticLevelObjects.emplace_back(std::make_shared<Border>(glm::vec2((m_blocksWidth+1) * m_BLOCK_SIZE, 0.f),
                                                               glm::vec2(m_BLOCK_SIZE*2, getLevelHeight())));
}


void Level::render() const
{
    for (const auto& object : m_staticLevelObjects)
        if (object)
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

EasyLevel::EasyLevel(const std::vector<std::string>& levelDescription,
                     size_t countOfRespawnSpots) : Level(levelDescription, countOfRespawnSpots)
{
    m_enemyRespawnSpots.reserve(m_countOfRespawnSpots);
    unsigned int YOffset = m_BLOCK_SIZE * (m_blocksHeight - 1) + m_BLOCK_SIZE / 2.f;
    unsigned int XOffset = m_BLOCK_SIZE;
    const std::string& firstRow = levelDescription[0];
    for (const char& currentDescription : firstRow)
    {
        if (currentDescription=='D' || currentDescription=='B' || currentDescription=='C')
            m_enemyRespawnSpots.push_back(glm::ivec2(XOffset, YOffset));
        XOffset += m_BLOCK_SIZE;
    }
}


