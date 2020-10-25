#pragma once

#include <string>
#include <map>
#include <memory>

namespace RenderEngine
{
    class ShaderProgram;
    class Texture2D;
    class Sprite;
    class AnimatedSprite;

}

class ResourceManager
{
    using MapShaderPrograms = std::map<std::string, std::shared_ptr<RenderEngine::ShaderProgram>>;
    using MapTextures = std::map<std::string, std::shared_ptr<RenderEngine::Texture2D>>;
    using MapSprites = std::map<std::string, std::shared_ptr<RenderEngine::Sprite>>;
    using MapAnimatedSprites = std::map<std::string, std::shared_ptr<RenderEngine::AnimatedSprite>>;

    static MapShaderPrograms  m_programs;
    static MapTextures        m_textures;
    static MapSprites         m_sprites;
    static MapAnimatedSprites m_animatedSprites;
    static std::string        m_path;

public:
    static void setExecutablePath(const std::string& executablePath);
    static void unloadResources();

    ResourceManager() = delete;
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
    ResourceManager(ResourceManager&&) = delete;
    ResourceManager& operator=(ResourceManager&&) = delete;
    ~ResourceManager() = delete;


    static std::shared_ptr<RenderEngine::ShaderProgram>
    loadShaders(const std::string& progName,
                const std::string& vertexPath,
                const std::string& fragmentPath);

    static std::shared_ptr<RenderEngine::ShaderProgram>
    getShaderProgram(const std::string& progName);

    static std::shared_ptr<RenderEngine::Texture2D>
    loadTexture(const std::string& textureName,
                const std::string& texturePath);

    static std::shared_ptr<RenderEngine::Texture2D>
    getTexture(const std::string& textureName);

    static std::shared_ptr<RenderEngine::Sprite>
    createSprite(const std::string& spriteName,
                 const std::string& shaderName,
                 const std::string& textureName,
                 const std::string& subTextureName,
                 const unsigned int width,
                 const unsigned int height);

    static std::shared_ptr<RenderEngine::Sprite>
    getSprite(const std::string& spriteName);


    static std::shared_ptr<RenderEngine::AnimatedSprite>
    createAnimatedSprite(const std::string& spriteName,
                         const std::string& shaderName,
                         const std::string& textureName,
                         const unsigned int width,
                         const unsigned int height);

    static std::shared_ptr<RenderEngine::AnimatedSprite>
    getAnimatedSprite(const std::string& spriteName);

private:
    static std::string getFileContent(const std::string& filePath);
};
