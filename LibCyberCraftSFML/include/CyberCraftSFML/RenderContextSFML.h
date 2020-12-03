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

namespace ccSf {
    class RenderContextSFML : public cc::RenderContext {
    public:
        explicit RenderContextSFML(sf::RenderTarget &target);

        cc::TextureHandle loadTexture(std::string_view filename) override;

        void unloadTexture(cc::TextureHandle texture) override;

        void drawSprite(cc::TextureHandle texture,
                        const cc::Vector2f &pos,
                        const cc::Vector2i &textureIndex,
                        cc::Color color,
                        cc::Color backgroundColor,
                        float rotation) override;

        void drawSprite(cc::TextureHandle texture,
                        const cc::Vector2f &pos,
                        float scale,
                        cc::Color color) override;

        void setViewCenter(cc::Vector2f pos) override;

    private:
        std::map<cc::TextureHandle, std::unique_ptr<sf::Texture>> m_texture;
        sf::RenderTarget &m_target;
        int m_nextId = 1;
    };
}

#endif //CYBERCRAFT_RENDERCONTEXTSFML_H
