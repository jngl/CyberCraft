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
    struct Texture{
        std::string fileName;
        std::unique_ptr<sf::Texture> sfTexture;
    };

    class RenderContextSFML : public ck::RenderContext2D {
    public:
        explicit RenderContextSFML(sf::RenderTarget &target);

        [[nodiscard]] ck::TextureHandle getHandleFromFile(std::string_view filename) override;
        void loadTexture(ck::TextureHandle handle) override;
        void unloadTexture(ck::TextureHandle handle) override;

        void drawSprite(ck::TextureHandle texture,
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
        cc::IdGenerator<ck::TextureHandle::ValueType, ck::TextureHandle::Tag> m_textureIdGenerator;
        std::vector<Texture> m_textures;
        sf::RenderTarget &m_target;
    };
}

#endif //CYBERCRAFT_RENDERCONTEXTSFML_H
