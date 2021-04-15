//
// Created by jngl on 14/04/2021.
//

#ifndef CYBERCRAFT_ENGINE2D_H
#define CYBERCRAFT_ENGINE2D_H

#include <Core/Texture.h>
#include <Core/Math.h>
#include <Core/Color.h>

namespace cc
{
    class SpriteDrawer
    {
    public:
        constexpr SpriteDrawer() = default;
        constexpr SpriteDrawer(const SpriteDrawer&) = default;
        constexpr SpriteDrawer(SpriteDrawer&&) = default;

        SpriteDrawer& operator=(const SpriteDrawer&) = default;
        SpriteDrawer& operator=(SpriteDrawer&&) = default;

        virtual ~SpriteDrawer() = default;

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

    class Camera2D
    {
    public:
        constexpr Camera2D() = default;
        constexpr Camera2D(const Camera2D&) = default;
        constexpr Camera2D(Camera2D&&) = default;

        Camera2D& operator=(const Camera2D&) = default;
        Camera2D& operator=(Camera2D&&) = default;

        virtual ~Camera2D() = default;

        virtual void setViewCenter(Vector2f pos) = 0;
    };

    class RenderContext2D : public TextureManager, public Camera2D, public SpriteDrawer  {
    public:
    };
}

#endif //CYBERCRAFT_ENGINE2D_H
