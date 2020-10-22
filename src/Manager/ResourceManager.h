#pragma once

#include <string>
#include <map>
#include <memory>

namespace Renderer
{
    class ShaderProgram;
    class Texture2D;
    class Sprite;
}

class ResourceManager
{
    using MapShaderPrograms = std::map<std::string, std::shared_ptr<Renderer::ShaderProgram>>;
    using MapTextures = std::map<std::string, std::shared_ptr<Renderer::Texture2D>>;
    using MapSprites = std::map<std::string, std::shared_ptr<Renderer::Sprite>>;

    MapShaderPrograms m_programs;
    MapTextures       m_textures;
    MapSprites        m_sprites;
    std::string       m_path;

public:
    ResourceManager(const std::string& executablePath);
    ~ResourceManager() = default;


    ResourceManager() = delete;
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
    ResourceManager(ResourceManager&&) = delete;
    ResourceManager& operator=(ResourceManager&&) = delete;

    std::shared_ptr<Renderer::ShaderProgram> loadShaders(const std::string& progName,
                                                         const std::string& vertexPath,
                                                         const std::string& fragmentPath);

    std::shared_ptr<Renderer::ShaderProgram> getShaderProgram(const std::string& progName) const;

    std::shared_ptr<Renderer::Texture2D> loadTexture(const std::string& textureName,
                                                     const std::string& texturePath);

    std::shared_ptr<Renderer::Texture2D> getTexture(const std::string& textureName);

    std::shared_ptr<Renderer::Sprite> createSprite(const std::string& spriteName,
                                                   const std::string& shaderName,
                                                   const std::string& textureName,
                                                   const std::string& subTextureName,
                                                   const unsigned int width,
                                                   const unsigned int height);

    std::shared_ptr<Renderer::Sprite> getSprite(const std::string& spriteName);

private:
    std::string getFileContent(const std::string& filePath);
};
