//
// Created by jngl on 14/04/2021.
//

#ifndef CYBERCRAFT_ENGINE2D_H
#define CYBERCRAFT_ENGINE2D_H

#include <Ports/Texture.h>

#include <Core/Math.h>
#include <CyberBase/Color.hpp>
#include <Core/Bases.h>

namespace ck
{
    class ColoredRectangleDrawer : public cc::Copyable
    {
    public:
        virtual void drawRectangle(const cc::Vector2f& pos, const cc::Vector2f& size, const cb::Color& color) = 0;
    };

    class SpriteDrawer : public cc::Copyable
    {
    public:
        virtual void drawSprite(const cp::Texture& texture,
                                const cc::Vector2f &pos,
                                const cc::Vector2i &textureIndex,
                                cb::Color color,
                                cb::Color backgroundColor,
                                float rotation) = 0;
    };

    class Camera2D : public cc::Copyable
    {
    public:
        virtual void setViewCenter(cc::Vector2f pos) = 0;
    };

class RenderContext2D : public cp::TextureFactory, public Camera2D, public SpriteDrawer  {
    public:
    };
}

#endif //CYBERCRAFT_ENGINE2D_H
