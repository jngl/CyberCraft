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
    class RenderContextSFML : public ccCore::RenderContext {
    public:
        explicit RenderContextSFML(sf::RenderTarget &target);

        ccCore::TextureHandle loadTexture(std::string_view filename) override;

        void unloadTexture(ccCore::TextureHandle texture) override;

        void drawSprite(ccCore::TextureHandle texture,
                        const ccCore::Vector2f &pos,
                        const ccCore::Vector2i &textureIndex,
                        ccCore::Color color,
                        ccCore::Color backgroundColor,
                        float rotation) override;

        void drawSprite(ccCore::TextureHandle texture,
                        const ccCore::Vector2f &pos,
                        float scale,
                        ccCore::Color color) override;

    private:
        std::map<ccCore::TextureHandle, std::unique_ptr<sf::Texture>> m_texture;
        sf::RenderTarget &m_target;
        int m_nextId = 1;
    };
}

#endif //CYBERCRAFT_RENDERCONTEXTSFML_H
