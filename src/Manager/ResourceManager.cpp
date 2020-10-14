#include "ResourceManager.h"

#include "../Renderer/ShaderProgram.h"
#include "../Renderer/Texture2D.h"
#include <fstream>
#include <iostream>
#include <sstream>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h"

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

std::shared_ptr<Renderer::Texture2D> ResourceManager::loadTexture(const std::string& textureName,
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
                                  std::make_shared<Renderer::Texture2D>(width,
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

std::shared_ptr<Renderer::Texture2D> ResourceManager::getTexture(const std::string& textureName)
{
    auto it = m_textures.find(textureName);
    if (it != m_textures.end())
        return it->second;
    std::cerr << "ResourceManager: Couldn't find texture with name'" << textureName << "'." << std::endl;
    return nullptr;
}
