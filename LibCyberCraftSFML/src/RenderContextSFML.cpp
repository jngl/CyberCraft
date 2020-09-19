//
// Created by jngl on 19/09/2020.
//

#include "CyberCraftSFML/RenderContextSFML.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "conversion.h"

RenderContextSFML::RenderContextSFML(sf::RenderTarget &target):
m_target(target){

}

TextureHandle RenderContextSFML::loadTexture(std::string_view filename){
    TextureHandle textureHandle{m_nextId++};
    std::unique_ptr<sf::Texture>& texturePtr =  m_texture[textureHandle];
    texturePtr = std::make_unique<sf::Texture>();
    texturePtr->loadFromFile(std::string(filename));
    return textureHandle;
}

void RenderContextSFML::unloadTexture(TextureHandle texture){
    m_texture.erase(texture);
}

void RenderContextSFML::drawSprite(TextureHandle textureHandle,
                            const math::Vector2f& pos,
                            const math::Vector2i& textureIndex,
                            Color color,
                            Color backgroundColor) {
    sf::Texture& texture = *m_texture[textureHandle];

    math::Vector2f a;

    sf::RectangleShape background;
    background.setPosition(toSfVector2(pos * 32.f));
    background.setSize(sf::Vector2f(32,32));
    background.setFillColor(toSfColor(backgroundColor));
    m_target.draw(background);

    sf::Sprite sfSprite;
    sfSprite.setScale(2,2);

    sfSprite.setPosition(toSfVector2(pos*32.f));
    sfSprite.setTextureRect(sf::IntRect(16*textureIndex.x, 16*textureIndex.y, 16, 16));
    sfSprite.setTexture(texture);
    sfSprite.setColor(toSfColor(color));
    m_target.draw(sfSprite);
}

void RenderContextSFML::drawSprite(TextureHandle textureHandle,
                            const math::Vector2f& pos,
                            float scale,
                            Color color) {
    sf::Texture& texture = *m_texture[textureHandle];
    sf::Sprite sfSprite;
    sfSprite.setTexture(texture);
    sfSprite.setPosition(toSfVector2(pos));
    sfSprite.setScale(scale, scale);
    sfSprite.setColor(toSfColor(color));
    m_target.draw(sfSprite);
}