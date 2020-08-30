//
// Created by jngl on 27/06/2020.
//

#ifndef CYBERCRAFT_WINDOW_H
#define CYBERCRAFT_WINDOW_H

#include <Core/Common.h>
#include <Core/Math.h>

class GraphicsContext
{
public:
    virtual TextureHandle loadTexture(std::string_view filename) = 0;
    virtual void unloadTexture(TextureHandle texture) = 0;

    virtual void drawSprite(TextureHandle texture,
                            const math::Vector2f& pos,
                            const math::Vector2i& textureIndex,
                            Color color,
                            Color backgroundColor) = 0;
};

class Window {
public:
    virtual ~Window() = default;
    virtual GraphicsContext& getGraphicsContext() = 0;

    [[nodiscard]] virtual bool isOpen() const = 0;
    virtual void beginFrame() = 0;
    virtual void endFrame() = 0;
};

#endif //CYBERCRAFT_WINDOW_H
