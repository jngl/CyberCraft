//
// Created by jngl on 19/09/2020.
//

#ifndef CYBERCRAFT_RENDERCONTEXT_H
#define CYBERCRAFT_RENDERCONTEXT_H

#include <Core/Id.h>
#include <Core/Common.h>
#include <Core/Math.h>

namespace ccCore {
    struct TextureHandle : public Id {
    };

    class RenderContext {
    public:
        virtual ~RenderContext() = default;

        virtual TextureHandle loadTexture(std::string_view filename) = 0;

        virtual void unloadTexture(TextureHandle texture) = 0;

        virtual void drawSprite(TextureHandle texture,
                                const Vector2f &pos,
                                const Vector2i &textureIndex,
                                Color color,
                                Color backgroundColor) = 0;

        virtual void drawSprite(TextureHandle texture,
                                const Vector2f &pos,
                                float scale,
                                Color color) = 0;
    };
}

#endif //CYBERCRAFT_RENDERCONTEXT_H
