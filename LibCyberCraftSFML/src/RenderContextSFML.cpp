//
// Created by jngl on 19/09/2020.
//

#include "CyberCraftSFML/RenderContextSFML.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "conversion.h"

namespace ccSf {
    RenderContextSFML::RenderContextSFML(sf::RenderTarget &target) :
            m_target(target) {

    }

    ccCore::TextureHandle RenderContextSFML::loadTexture(std::string_view filename) {
        ccCore::TextureHandle textureHandle{m_nextId++};
        std::unique_ptr<sf::Texture> &texturePtr = m_texture[textureHandle];
        texturePtr = std::make_unique<sf::Texture>();
        texturePtr->loadFromFile(std::string(filename));
        return textureHandle;
    }

    void RenderContextSFML::unloadTexture(ccCore::TextureHandle texture) {
        m_texture.erase(texture);
    }

    void RenderContextSFML::drawSprite(ccCore::TextureHandle textureHandle,
                                       const ccCore::Vector2f &pos,
                                       const ccCore::Vector2i &textureIndex,
                                       ccCore::Color color,
                                       ccCore::Color backgroundColor,
                                       float rotation) {
        sf::Texture &texture = *m_texture[textureHandle];

        ccCore::Vector2f a;

        sf::RectangleShape background;
        background.setPosition(pos.x*32+16, pos.y*32+16);
        background.setSize(sf::Vector2f(32, 32));
        background.setFillColor(toSfColor(backgroundColor));
        background.setOrigin(16,16);
        background.setRotation(rotation);
        m_target.draw(background);

        sf::Sprite sfSprite;
        sfSprite.setScale(2, 2);

        sfSprite.setPosition(pos.x*32.f+16, pos.y*32.f+16);
        sfSprite.setTextureRect(sf::IntRect(16 * textureIndex.x, 16 * textureIndex.y, 16, 16));
        sfSprite.setTexture(texture);
        sfSprite.setColor(toSfColor(color));
        sfSprite.setOrigin(8,8);
        sfSprite.setRotation(rotation);
        m_target.draw(sfSprite);
    }

    void RenderContextSFML::drawSprite(ccCore::TextureHandle textureHandle,
                                       const ccCore::Vector2f &pos,
                                       float scale,
                                       ccCore::Color color) {
        sf::Texture &texture = *m_texture[textureHandle];
        sf::Sprite sfSprite;
        sfSprite.setTexture(texture);
        sfSprite.setPosition(toSfVector2(pos));
        sfSprite.setScale(scale, scale);
        sfSprite.setColor(toSfColor(color));
        m_target.draw(sfSprite);
    }

    void RenderContextSFML::setViewCenter(ccCore::Vector2f pos) {
        sf::View view(m_target.getView());
        view.setCenter(toSfVector2(pos*32.f));
        m_target.setView(view);
    }
}