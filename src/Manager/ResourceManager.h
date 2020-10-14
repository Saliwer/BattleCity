#pragma once

#include <string>
#include <map>
#include <memory>

namespace Renderer
{
    class ShaderProgram;
}

class ResourceManager
{
    using pShaderProgram = std::shared_ptr<Renderer::ShaderProgram>;
    using MapShaderPrograms = std::map<std::string, pShaderProgram>;

    MapShaderPrograms m_programs;
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

private:
    std::string getFileContent(const std::string& filePath);

};
