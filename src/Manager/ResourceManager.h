#pragma once

#include <string>
#include <map>
#include <memory>

namespace Renderer
{
    class ShaderProgram;
    class Texture2D;
}

class ResourceManager
{
    using MapShaderPrograms = std::map<std::string, std::shared_ptr<Renderer::ShaderProgram>>;
    using MapTextures = std::map<std::string, std::shared_ptr<Renderer::Texture2D>>;

    MapShaderPrograms m_programs;
    MapTextures       m_textures;
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


private:
    std::string getFileContent(const std::string& filePath);
};
