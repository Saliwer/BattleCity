#include "Level.h"
#include "../Manager/ResourceManager.h"
#include "GameObjects/BrickWall.h"

#include <iostream>




std::shared_ptr<IGameObject>
createGameObjectFromChar(const char description,
                         const glm::vec2& position,
                         const glm::vec2& size,
                         const glm::vec2& direction)
{
    switch (description) {
    case '0':
        return std::make_shared<BrickWall>(ResourceManager::getSprite("rightBrick"), position, size, direction);
        break;
    case '1':
        return std::make_shared<BrickWall>(ResourceManager::getSprite("bottomBrick"), position, size, direction);
        break;
    case '2':
        return std::make_shared<BrickWall>(ResourceManager::getSprite("leftBrick"), position, size, direction);
        break;
    case '3':
        return std::make_shared<BrickWall>(ResourceManager::getSprite("topBrick"), position, size, direction);
        break;
    case '4':
        return std::make_shared<BrickWall>(ResourceManager::getSprite("fullBrick"), position, size, direction);
        break;
    case 'G':
        return std::make_shared<BrickWall>(ResourceManager::getSprite("bottomLeftBrick"), position, size, direction);
        break;
    case 'H':
        return std::make_shared<BrickWall>(ResourceManager::getSprite("bottomRightBrick"), position, size, direction);
        break;
    case 'I':
        return std::make_shared<BrickWall>(ResourceManager::getSprite("topLeftBrick"), position, size, direction);
        break;
    case 'J':
        return std::make_shared<BrickWall>(ResourceManager::getSprite("topRightBrick"), position, size, direction);
        break;
    case 'D':
        return nullptr;
        break;
    default:
        std::cerr << "Unknown char description '" << description <<
                     "'.\n";
        break;
    }
    return nullptr;
}


Level::Level(const std::vector<std::string>& levelDescription)
{
    if (levelDescription.empty())
    {
        std::cerr << "Couldn't create level! Empty level description!\n";
        return;
    }

    m_width = levelDescription[0].length();
    m_height = levelDescription.size();
    m_levelObjects.reserve(m_width * m_height);
    const unsigned int BLOCK_SIZE = 16;
    unsigned int YOffset = BLOCK_SIZE * (m_height - 1);
    for (const std::string& currentRow : levelDescription)
    {
        unsigned int XOffset = 0;
        for (const char currentDescription : currentRow)
        {
            m_levelObjects.emplace_back(createGameObjectFromChar(currentDescription,
                                                                 glm::vec2(XOffset, YOffset),
                                                                 glm::vec2(BLOCK_SIZE, BLOCK_SIZE),
                                                                 glm::vec2(1.f, 0.f)));
            XOffset += BLOCK_SIZE;
        }
        YOffset -= BLOCK_SIZE;
    }
}


void Level::render() const
{
    for (const auto& object : m_levelObjects)
        if (object)
            object->render();
}

void Level::update(uint64_t delta)
{
    for (const auto& object : m_levelObjects)
        if (object)
            object->update(delta);
}
