#include "ResourceManager.h"

#include "../Renderer/AnimatedSprite.h"
#include "../Renderer/Texture2D.h"
#include "../Renderer/Sprite.h"
#include "../Renderer/AnimatedSprite.h"
#include "../Renderer/ShaderProgram.h"

#include <rapidjson/document.h>
#include <rapidjson/error/en.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <cassert>
#include <list>
#include <vector>
#include <string>
//#define NDEBUG

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h"

#include <glm/vec2.hpp>

ResourceManager::MapShaderPrograms  ResourceManager::m_programs;
ResourceManager::MapTextures        ResourceManager::m_textures;
ResourceManager::MapSprites         ResourceManager::m_sprites;
ResourceManager::MapAnimatedSprites ResourceManager::m_animatedSprites;
std::string                         ResourceManager::m_path;


void ResourceManager::setExecutablePath(const std::string& executablePath)
{
    size_t found = executablePath.find_last_of("/\\");
    m_path = executablePath.substr(0, found);
}

void ResourceManager::unloadResources()
{
    m_programs.clear();
    m_textures.clear();
    m_sprites.clear();
    m_animatedSprites.clear();
    m_path.clear();

}


std::shared_ptr<RenderEngine::ShaderProgram>
ResourceManager::loadShaders(const std::string& progName,
                             const std::string& vertexPath,
                             const std::string& fragmentPath)
{
    std::string vertexCode = getFileContent(vertexPath);
    if (vertexCode.empty())
    {
        std::cerr << "ResourceManager: couldn't get source code for vertex shader.\n";
        return nullptr;
    }

    std::string fragmentCode = getFileContent(fragmentPath);
    if (fragmentCode.empty())
    {
        std::cerr << "ResourceManager: couldn't get source code for fragment shader.\n";
        return nullptr;
    }

    auto res = m_programs.emplace(progName, std::make_shared<RenderEngine::ShaderProgram>(vertexCode, fragmentCode));
    if (!res.second)
    {
        std::cerr << "ResourceManager: couldn't insert new shader program '" << progName << "'\n";
        return nullptr;
    }

    std::shared_ptr<RenderEngine::ShaderProgram>& newProgram = res.first->second;
    if (newProgram->isCompiled())
        return newProgram;

    std::cerr << "ResourceManager: couldn't load shader program:\n" <<
                 "Vertex: " << vertexPath << '\n' <<
                 "Fragment: " << fragmentPath << std::endl;
    return nullptr;

}

std::shared_ptr<RenderEngine::ShaderProgram>
ResourceManager::getShaderProgram(const std::string& progName)
{
    auto it = m_programs.find(progName);
    if (it != m_programs.end())
        return it->second;
    std::cerr << "ResourceManager: Couldn't find shader program with name'" << progName << "'." << std::endl;
    return nullptr;
}


std::string ResourceManager::getFileContent(const std::string& filePath)
{
    std::ifstream f;
    f.open(m_path + "/" + filePath, std::ios::in | std::ios::binary);
    if (!f.is_open()){
        std::cerr << "ResourceManager: couldn't open file: " << filePath << std::endl;
        return std::string{};
    }

    std::stringstream s;
    s << f.rdbuf();
    return s.str();
}

std::shared_ptr<RenderEngine::Texture2D>
ResourceManager::loadTexture(const std::string& textureName,
                             const std::string& texturePath)
{
    int width = 0;
    int height = 0;
    int channels = 0;

    stbi_set_flip_vertically_on_load(true);
    unsigned char* pixels = stbi_load(std::string(m_path + "/" + texturePath).c_str(), &width, &height, &channels, 0);
    if (!pixels)
    {
        std::cerr << "ResourseManager: Couldn't load the texture image: " << texturePath << std::endl;
        return nullptr;
    }

    auto res = m_textures.emplace(textureName,
                                  std::make_shared<RenderEngine::Texture2D>(width,
                                                                        height,
                                                                        channels,
                                                                        pixels,
                                                                        GL_CLAMP_TO_EDGE,
                                                                        GL_NEAREST));
    if (!res.second)
    {
        std::cerr << "ResourceManager: Couldn't insert the new texture: " << textureName << std::endl;
        return nullptr;
    }

    stbi_image_free(pixels);
    return res.first->second;
}

std::shared_ptr<RenderEngine::Texture2D>
ResourceManager::getTexture(const std::string& textureName)
{
    auto it = m_textures.find(textureName);
    if (it != m_textures.end())
        return it->second;
    std::cerr << "ResourceManager: Couldn't find texture with name'" << textureName << "'." << std::endl;
    return nullptr;
}

std::shared_ptr<RenderEngine::Sprite>
ResourceManager::createSprite(const std::string& spriteName,
                              const std::string& shaderName,
                              const std::string& textureName,
                              const std::string& subTextureName,
                              const unsigned int width,
                              const unsigned int height)
{
    std::shared_ptr<RenderEngine::ShaderProgram> pShaderProgram = getShaderProgram(shaderName);
    if (!pShaderProgram)
    {
        std::cerr << "ResourceManager: Couldn't create the new sprite '" <<
        spriteName << "'\n";
        return nullptr;
    }

    std::shared_ptr<RenderEngine::Texture2D> pTexture = getTexture(textureName);
    if (!pTexture)
    {
        std::cerr << "ResourceManager: Couldn't create the new sprite '" <<
        spriteName << "'\n";
        return nullptr;
    }

    auto res = m_sprites.emplace(spriteName,
                                 std::make_shared<RenderEngine::Sprite>(pShaderProgram,
                                                                    pTexture,
                                                                    subTextureName,
                                                                    glm::vec2(0.f, 0.f),
                                                                    glm::vec2(width, height)));
    if (!res.second)
    {
        std::cerr << "ResourceManager: Couldn't insert the new sprite: " << spriteName << std::endl;
        return nullptr;
    }

    return res.first->second;
}

std::shared_ptr<RenderEngine::Sprite>
ResourceManager::getSprite(const std::string& spriteName)
{
    auto it = m_sprites.find(spriteName);
    if (it != m_sprites.end())
        return it->second;
    std::cerr << "ResourceManager: Couldn't find a sprite with name'" << spriteName << "'." << std::endl;
    return nullptr;
}

std::shared_ptr<RenderEngine::AnimatedSprite>
ResourceManager::createAnimatedSprite(const std::string& spriteName,
                                      const std::string& shaderName,
                                      const std::string& textureName,
                                      const unsigned int width,
                                      const unsigned int height)
{
    std::shared_ptr<RenderEngine::ShaderProgram> pShaderProgram = getShaderProgram(shaderName);
    if (!pShaderProgram)
    {
        std::cerr << "ResourceManager: Couldn't create the new animated sprite '" <<
        spriteName << "'\n";
        return nullptr;
    }

    std::shared_ptr<RenderEngine::Texture2D> pTexture = getTexture(textureName);
    if (!pTexture)
    {
        std::cerr << "ResourceManager: Couldn't create the animated new sprite '" <<
        spriteName << "'\n";
        return nullptr;
    }

    auto res = m_animatedSprites.emplace(spriteName,
                                         std::make_shared<RenderEngine::AnimatedSprite>
                                         (pShaderProgram, pTexture,
                                          glm::vec2(0.f, 0.f), glm::vec2(width, height)));
    if (!res.second)
    {
        std::cerr << "ResourceManager: Couldn't insert the new animated sprite: " <<
        spriteName << std::endl;
        return nullptr;
    }
    return res.first->second;
}

std::shared_ptr<RenderEngine::AnimatedSprite>
ResourceManager::getAnimatedSprite(const std::string& spriteName)
{
    auto it = m_animatedSprites.find(spriteName);
    if (it != m_animatedSprites.end())
        return it->second;
    std::cerr << "ResourceManager: Couldn't find an animated sprite with name'" <<
    spriteName << "'." << std::endl;
    return nullptr;
}


bool ResourceManager::loadJSONResources(const std::string& JSONpath)
{
    const std::string JSONstring = getFileContent(JSONpath);
    if (JSONstring.empty())
    {
        std::cerr << "ResourceManager: No JSON resource file!\n";
        return false;
    }

    rapidjson::Document JSON_document;
    rapidjson::ParseResult parseResult = JSON_document.Parse(JSONstring.c_str());
    if (!parseResult)
    {
        std::cerr << "ResourceManager: JSON parse error: " << rapidjson::GetParseError_En(parseResult.Code()) <<
        "(" << parseResult.Offset() << ")" << std::endl;
        return false;
    }

    // Parsing shaders
    assert(JSON_document.HasMember("shaders") && "There is no shaders in *.json file");
    rapidjson::Document::ConstMemberIterator shadersIt = JSON_document.FindMember("shaders");
    for (const auto& currentShader : shadersIt->value.GetArray())
    {
        const std::string name = currentShader["name"].GetString();
        const std::string filePath_vs = currentShader["filePath_vs"].GetString();
        const std::string filePath_fs = currentShader["filePath_fs"].GetString();
        loadShaders(name, filePath_vs, filePath_fs);
    }

    //Parsing textures
    assert(JSON_document.HasMember("textureAtlases") && "There is no texture atlasses in *.json file");
    rapidjson::Document::ConstMemberIterator textureAtlassesIt = JSON_document.FindMember("textureAtlases");
    for (const auto& currentTextureAtlas : textureAtlassesIt->value.GetArray())
    {
        std::string textureName = currentTextureAtlas["textureName"].GetString();
        std::string filePath = currentTextureAtlas["filePath"].GetString();
        unsigned int subTextureWidth = currentTextureAtlas["subTextureWidth"].GetUint();
        unsigned int subTextureHeight = currentTextureAtlas["subTextureHeight"].GetUint();
        auto pTexture = loadTexture(textureName, filePath);
        const auto& subTexturesArray = currentTextureAtlas["subTextures"].GetArray();
        std::vector<std::string> subTextures;
        for(const auto& currentSubTexture : subTexturesArray)
            subTextures.emplace_back(std::move(currentSubTexture.GetString()));
        pTexture->genSubTextures(std::move(subTextures), glm::vec2(0.f, pTexture->getHeight()),
                                glm::vec2((float)subTextureWidth, (float)subTextureHeight));
    }

    //Parsing animated sprites
    assert(JSON_document.HasMember("animatedSprites") && "There is no animated sprites in *.json file");
    rapidjson::Document::ConstMemberIterator animSpritesIt = JSON_document.FindMember("animatedSprites");
    for(const auto& currentSprite : animSpritesIt->value.GetArray())
    {
        std::string spriteName = currentSprite["name"].GetString();
        std::string shaderProgram = currentSprite["shader"].GetString();
        std::string textureName = currentSprite["textureName"].GetString();
        unsigned int initialWidth = currentSprite["initialWidth"].GetUint();
        unsigned int initialHeight = currentSprite["initialHeight"].GetUint();
        std::string initialSubTexture = currentSprite["initialSubTexture"].GetString();

        auto pAnimeSprite = createAnimatedSprite(spriteName, shaderProgram, textureName,
                                                 initialWidth, initialHeight);
        if (!pAnimeSprite)
            continue;

        const auto& statesArray = currentSprite["spriteStates"].GetArray();
        for (const auto& currentState : statesArray)
        {
            std::string stateName = currentState["spriteState"].GetString();
            std::list<std::pair<std::string, uint64_t>> framesList;
            const auto& framesArray = currentState["frames"].GetArray();
            for(const auto& frame : framesArray)
            {
                std::string subTexture = frame["subTexture"].GetString();
                uint64_t duration = frame["duration"].GetUint64();
                framesList.emplace_back(std::move(subTexture), duration);
            }
            pAnimeSprite->insertState(std::move(stateName), std::move(framesList));
        }
        pAnimeSprite->setState(initialSubTexture);
    }


    return true;
}
