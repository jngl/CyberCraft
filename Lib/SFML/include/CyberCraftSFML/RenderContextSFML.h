//
// Created by jngl on 19/09/2020.
//

#ifndef CYBERCRAFT_RENDERCONTEXTSFML_H
#define CYBERCRAFT_RENDERCONTEXTSFML_H

#include <Kernel/Engine2D.h>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <memory>
#include <map>

namespace ccSf {
    class Texture : public cp::Texture{
    public:
        std::string fileName;
        sf::Texture sfTexture;
    };

    class RenderContextSFML : public ck::RenderContext2D {
    public:
        explicit RenderContextSFML(sf::RenderTarget &target);

        std::shared_ptr<cp::Texture> loadTextureFromFile(std::string_view filename) override;

        void drawSprite(const cp::Texture& texture,
                        const cc::Vector2f &pos,
                        const cc::Vector2i &textureIndex,
                        cc::Color color,
                        cc::Color backgroundColor,
                        float rotation) override;

       /* void drawSprite(ck::TextureHandle texture,
                        const cc::Vector2f &pos,
                        float scale,
                        cc::Color color) override;*/

        void setViewCenter(cc::Vector2f pos) override;

    private:
        std::vector<std::shared_ptr<Texture>> m_textures;
        sf::RenderTarget &m_target;
    };
}

#endif //CYBERCRAFT_RENDERCONTEXTSFML_H
