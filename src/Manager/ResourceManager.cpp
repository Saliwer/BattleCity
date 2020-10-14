#include "ResourceManager.h"

#include "../Renderer/ShaderProgram.h"

#include <fstream>
#include <iostream>
#include <sstream>

ResourceManager::ResourceManager(const std::string& executablePath)
{
    size_t found = executablePath.find_last_of("/\\");
    m_path = executablePath.substr(0, found);
}

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::loadShaders(const std::string& progName,
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

    auto res = m_programs.emplace(progName, std::make_shared<Renderer::ShaderProgram>(vertexCode, fragmentCode));
    if (!res.second)
    {
        std::cerr << "ResourceManager: couldn't insert new shader program '" << progName << "'\n";
        return nullptr;
    }

    std::shared_ptr<Renderer::ShaderProgram>& newProgram = res.first->second;
    if (newProgram->isCompiled())
        return newProgram;

    std::cerr << "ResourceManager: couldn't load shader program:\n" <<
                 "Vertex: " << vertexPath << '\n' <<
                 "Fragment: " << fragmentPath << std::endl;
    return nullptr;

}

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::getShaderProgram(const std::string& progName) const
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
