#include "Game.h"

#include <vector>
#include <memory>

#include "../Manager/ResourceManager.h"
#include "../Renderer/ShaderProgram.h"
#include "../Renderer/Texture2D.h"
#include "../Renderer/Sprite.h"
#include "../Renderer/AnimatedSprite.h"

#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

Game::Game(const glm::ivec2& windowSize) : m_windowSize(windowSize),
                                           m_gameState(EGameState::ACTIVE)
{
    m_keys.fill(false);
}

Game::~Game()
{}

bool Game::init()
{
    std::shared_ptr<Renderer::ShaderProgram> shaderProgram =
        ResourceManager::loadShaders("FirstProgram",
                               "resource/shaders/vertex.vs",
                               "resource/shaders/fragment.fs");
    if (!shaderProgram)
        return false;

    std::shared_ptr<Renderer::Texture2D> myTexture =
        ResourceManager::loadTexture("FirstTexture",
                               "resource/textures/map_16x16.png");
    if (!myTexture)
        return false;


    std::vector<std::string> subTextures = {"Brick", "BrickTop", "BrickBottom", "BrickLeft",
                                            "BrickRight", "BrickTopLeft", "BrickTopRight",
                                            "BrickBottomLeft", "BrickBottomRight", "Beton"};

    myTexture->genSubTextures(subTextures, glm::vec2(0.f, (float)myTexture->getHeight()), glm::vec2(16.f, 16.f));

    std::shared_ptr<Renderer::Sprite> brickSprite =
        ResourceManager::createSprite("BrickSprite", "FirstProgram", "FirstTexture", "Brick", 50, 50);
    brickSprite->setPosition(glm::vec2(300.f, 100.f));

    std::shared_ptr<Renderer::Sprite> betonSprite =
        ResourceManager::createSprite("BetonSprite", "FirstProgram", "FirstTexture", "Beton", 50, 50);
    betonSprite->setPosition(glm::vec2(250.f, 100.f));
    betonSprite->setSubTexture("BrickTopLeft");

    std::shared_ptr<Renderer::AnimatedSprite> pAnimeSprite =
        ResourceManager::createAnimatedSprite("AnimeSprite", "FirstProgram", "FirstTexture", 50, 50);

    pAnimeSprite->setPosition(glm::vec2(100.f, 100.f));

    for (auto& elem : subTextures)
        pAnimeSprite->addSubTexture(elem, 1e9);

    glm::mat4 projectionMatrix = glm::ortho(0.0f, (float)m_windowSize.x,
                                            0.0f, (float)m_windowSize.y,
                                            100.0f, -100.0f);


    shaderProgram->use();
    shaderProgram->setUniform("projectionMatrix", projectionMatrix);
    shaderProgram->setUniform("myTexture", 0);
    shaderProgram->unUse();

    return true;
}

void Game::render()
{
    ResourceManager::getAnimatedSprite("AnimeSprite")->render();
}

void Game::update(uint64_t deltaTime)
{
    ResourceManager::getAnimatedSprite("AnimeSprite")->update(deltaTime);
}

void Game::setKey(int key, int action)
{
    if (action == GLFW_PRESS)
        m_keys[key] = true;
    else if (action == GLFW_RELEASE)
        m_keys[key] = false;
}
