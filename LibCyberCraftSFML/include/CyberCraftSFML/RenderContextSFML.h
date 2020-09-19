//
// Created by jngl on 19/09/2020.
//

#ifndef CYBERCRAFT_RENDERCONTEXTSFML_H
#define CYBERCRAFT_RENDERCONTEXTSFML_H

#include <Core/RenderContext.h>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <memory>
#include <map>

class RenderContextSFML : public RenderContext {
public:
    explicit RenderContextSFML(sf::RenderTarget& target);

    TextureHandle loadTexture(std::string_view filename) override;
    void unloadTexture(TextureHandle texture) override;

    void drawSprite(TextureHandle texture,
                    const math::Vector2f& pos,
                    const math::Vector2i& textureIndex,
                    Color color,
                    Color backgroundColor) override;

    void drawSprite(TextureHandle texture,
                    const math::Vector2f& pos,
                    float scale,
                    Color color) override;

private:
    std::map<TextureHandle, std::unique_ptr<sf::Texture>> m_texture;
    sf::RenderTarget& m_target;
    int m_nextId = 1;
};


#endif //CYBERCRAFT_RENDERCONTEXTSFML_H
