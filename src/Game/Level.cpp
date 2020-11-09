#include "Level.h"

#include "GameObjects/BrickWall.h"
#include "GameObjects/BetonWall.h"
#include "GameObjects/Tree.h"
#include "GameObjects/Ice.h"
#include "GameObjects/Water.h"
#include "GameObjects/Eagle.h"

#include <iostream>




std::shared_ptr<IGameObject>
createGameObjectFromChar(const char description,
                         const glm::vec2& position,
                         const glm::vec2& size,
                         const glm::vec2& direction)
{
    switch (description) {
    case '0':
        return std::make_shared<BrickWall>(BrickWall::EBrickWallType::Right, position, size, direction);
    case '1':
        return std::make_shared<BrickWall>(BrickWall::EBrickWallType::Bottom, position, size, direction);
    case '2':
        return std::make_shared<BrickWall>(BrickWall::EBrickWallType::Left, position, size, direction);
    case '3':
        return std::make_shared<BrickWall>(BrickWall::EBrickWallType::Top, position, size, direction);
    case '4':
        return std::make_shared<BrickWall>(BrickWall::EBrickWallType::All, position, size, direction);
    case 'G':
        return std::make_shared<BrickWall>(BrickWall::EBrickWallType::BottomLeft, position, size, direction);
    case 'H':
        return std::make_shared<BrickWall>(BrickWall::EBrickWallType::BottomRight, position, size, direction);
    case 'I':
        return std::make_shared<BrickWall>(BrickWall::EBrickWallType::TopLeft, position, size, direction);
    case 'J':
        return std::make_shared<BrickWall>(BrickWall::EBrickWallType::TopRight, position, size, direction);
    case 'D':
        return nullptr;
    case '5':
        return std::make_shared<BetonWall>(BetonWall::EBetonWallType::Right, position, size, direction);
    case '6':
        return std::make_shared<BetonWall>(BetonWall::EBetonWallType::Bottom, position, size, direction);
    case '7':
        return std::make_shared<BetonWall>(BetonWall::EBetonWallType::Left, position, size, direction);
    case '8':
        return std::make_shared<BetonWall>(BetonWall::EBetonWallType::Top, position, size, direction);
    case '9':
        return std::make_shared<BetonWall>(BetonWall::EBetonWallType::All, position, size, direction);
    case 'A':
        return std::make_shared<Water>(position, size, direction);
    case 'B':
        return std::make_shared<Tree>(position, size, direction);
    case 'C':
        return std::make_shared<Ice>(position, size, direction);
    case 'E':
        return std::make_shared<Eagle>(true, position, size, direction);
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
