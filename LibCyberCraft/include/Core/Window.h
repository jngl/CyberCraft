//
// Created by jngl on 27/06/2020.
//

#ifndef CYBERCRAFT_WINDOW_H
#define CYBERCRAFT_WINDOW_H

#include <Core/Common.h>
#include <Core/Math.h>
#include <Core/Id.h>

struct TextureHandle : public Id{
};

class Window {
public:
    virtual ~Window() = default;

    [[nodiscard]] virtual bool isOpen() const = 0;
    virtual void beginFrame() = 0;
    virtual void endFrame() = 0;

    virtual TextureHandle loadTexture(std::string_view filename) = 0;
    virtual void unloadTexture(TextureHandle texture) = 0;

    virtual void drawSprite(TextureHandle texture,
                            const math::Vector2f& pos,
                            const math::Vector2i& textureIndex,
                            Color color,
                            Color backgroundColor) = 0;

    virtual void drawSprite(TextureHandle texture,
                            const math::Vector2f& pos,
                            float scale,
                            Color color) = 0;
};

#endif //CYBERCRAFT_WINDOW_H
