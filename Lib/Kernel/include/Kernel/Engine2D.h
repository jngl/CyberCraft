//
// Created by jngl on 14/04/2021.
//

#ifndef CYBERCRAFT_ENGINE2D_H
#define CYBERCRAFT_ENGINE2D_H

#include <Kernel/Texture.h>

#include <Core/Math.h>
#include <Core/Color.h>
#include <Core/Bases.h>

namespace ck
{
    class ColoredRectangleDrawer : public cc::Copyable
    {
    public:
        virtual void drawRectangle(const cc::Vector2f& pos, const cc::Vector2f& size, const cc::Color& color) = 0;
    };

    class SpriteDrawer : public cc::Copyable
    {
    public:
        virtual void drawSprite(TextureHandle texture,
                                const cc::Vector2f &pos,
                                const cc::Vector2i &textureIndex,
                                cc::Color color,
                                cc::Color backgroundColor,
                                float rotation) = 0;

        /*virtual void drawSprite(TextureHandle texture,
                                const cc::Vector2f &pos,
                                float scale,
                                cc::Color color) = 0;*/
    };

    class Camera2D : public cc::Copyable
    {
    public:
        virtual void setViewCenter(cc::Vector2f pos) = 0;
    };

    class RenderContext2D : public TextureManager, public Camera2D, public SpriteDrawer  {
    public:
    };
}

#endif //CYBERCRAFT_ENGINE2D_H
