//
// Created by jngl on 14/04/2021.
//

#ifndef CYBERCRAFT_ENGINE2D_H
#define CYBERCRAFT_ENGINE2D_H

#include <Core/Texture.h>
#include <Core/Math.h>
#include <Core/Color.h>
#include <Core/Bases.h>

namespace cc
{
    class ColoredRectangleDrawer : public Copyable
    {
    public:
        virtual void drawRectangle(const Vector2f& pos, const Vector2f& size, const Color& color) = 0;
    };

    class SpriteDrawer : public Copyable
    {
    public:
        virtual void drawSprite(TextureHandle texture,
                                const Vector2f &pos,
                                const Vector2i &textureIndex,
                                Color color,
                                Color backgroundColor,
                                float rotation) = 0;

        virtual void drawSprite(TextureHandle texture,
                                const Vector2f &pos,
                                float scale,
                                Color color) = 0;
    };

    class Camera2D : public Copyable
    {
    public:
        virtual void setViewCenter(Vector2f pos) = 0;
    };

    class RenderContext2D : public TextureManager, public Camera2D, public SpriteDrawer  {
    public:
    };
}

#endif //CYBERCRAFT_ENGINE2D_H
