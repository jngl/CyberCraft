//
// Created by jngl on 19/09/2020.
//

#include "CyberCraftSFML/RenderContextSFML.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "conversion.h"

constexpr auto tileTextureSize = 16;
constexpr auto tileTextureCenter = tileTextureSize / 2;
constexpr auto tileSize = static_cast<float>(tileTextureSize)*2.f;
constexpr auto tileOffset = tileSize / 2;

namespace ccSf {
    RenderContextSFML::RenderContextSFML(sf::RenderTarget &target) :
            m_target(target) {

    }

    cc::TextureHandle RenderContextSFML::loadTexture(std::string_view filename) {
        cc::TextureHandle textureHandle = m_textureIdGenerator.create();

        if(textureHandle.value() > m_textures.size()){
            m_textures.resize(textureHandle.value());
        }

        std::unique_ptr<sf::Texture> &texturePtr = m_textures[textureHandle.value()];
        texturePtr = std::make_unique<sf::Texture>();
        texturePtr->loadFromFile(std::string(filename));
        return textureHandle;
    }

    void RenderContextSFML::unloadTexture(cc::TextureHandle texture) {
        if(!texture.isValid() && texture.value()>=m_textures.size()){
            return;
        }
        m_textures[texture.value()].reset();
    }

    void RenderContextSFML::drawSprite(cc::TextureHandle textureHandle,
                                       const cc::Vector2f &pos,
                                       const cc::Vector2i &textureIndex,
                                       cc::Color color,
                                       cc::Color backgroundColor,
                                       float rotation){

        sf::Texture &texture = *m_textures[textureHandle.value()];

        cc::Vector2f a;

        sf::RectangleShape background;

        background.setPosition(pos.x * tileSize + tileOffset, pos.y * tileSize + tileOffset);
        background.setSize(sf::Vector2f(tileSize, tileSize));
        background.setFillColor(toSfColor(backgroundColor));
        background.setOrigin(tileOffset,tileOffset);
        background.setRotation(rotation);
        m_target.draw(background);

        sf::Sprite sfSprite;
        sfSprite.setScale(2, 2);

        sfSprite.setPosition(pos.x * tileSize + tileOffset, pos.y * tileSize + tileOffset);
        sfSprite.setTextureRect(sf::IntRect(tileTextureSize * textureIndex.x,
                                            tileTextureSize * textureIndex.y,
                                            tileTextureSize,
                                            tileTextureSize));
        sfSprite.setTexture(texture);
        sfSprite.setColor(toSfColor(color));
        sfSprite.setOrigin(tileTextureCenter,tileTextureCenter);
        sfSprite.setRotation(rotation);
        m_target.draw(sfSprite);
    }

    void RenderContextSFML::drawSprite(cc::TextureHandle textureHandle,
                                       const cc::Vector2f &pos,
                                       float scale,
                                       cc::Color color) {
        sf::Texture &texture = *m_textures[textureHandle.value()];
        sf::Sprite sfSprite;
        sfSprite.setTexture(texture);
        sfSprite.setPosition(toSfVector2(pos));
        sfSprite.setScale(scale, scale);
        sfSprite.setColor(toSfColor(color));
        m_target.draw(sfSprite);
    }

    void RenderContextSFML::setViewCenter(cc::Vector2f pos) {
        sf::View view(m_target.getView());
        view.setCenter(toSfVector2(pos*tileSize));
        m_target.setView(view);
    }
}
