#pragma once
#include "Sprite.h"
#include <list>
#include <map>
#include <utility>

namespace Renderer
{

class AnimatedSprite : public Sprite
{
    using ListTextures = std::list<std::pair<std::string, uint64_t>>;
    using HashStates = std::map<std::string, ListTextures>;

    HashStates                   m_states;
    ListTextures::const_iterator m_activeSubTexture;
    HashStates::const_iterator   m_activeState;
    uint64_t                     m_currentSpriteDuration;
public:
    AnimatedSprite(std::shared_ptr<ShaderProgram> pShaderProg,
                   std::shared_ptr<Texture2D> pTexture,
                   const glm::vec2& position = glm::vec2(0.f),
                   const glm::vec2& size = glm::vec2(1.f),
                   float rotation = 0.f);

    virtual ~AnimatedSprite();

    /*
    template <typename Name, typename List>
    void insertState(Name&& name, List&& subTextures)
    {
        m_states.emplace(std::forward<Name>(name), std::forward<List>(subTextures));
    }
    */
    void insertState(std::string name, ListTextures subTextures);

    const std::string& getActiveState() const { return m_activeState->first; }
    void setState(const std::string& newState);

    void update(uint64_t delta);
    virtual void render() override;

};

}
