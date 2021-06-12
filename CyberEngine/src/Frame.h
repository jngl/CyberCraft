//
// Created by jngl on 04/06/2021.
//

#ifndef CYBERCRAFT_FRAME_H
#define CYBERCRAFT_FRAME_H

#include <Core/Engine.h>

#include "Renderer2d.h"

class Frame final : public cc::ColoredRectangleDrawer {
public:
    friend class Context;

    Frame(const Frame&) = delete;
    Frame(Frame&&) = delete;
    Frame& operator=(const Frame&) = delete;
    Frame& operator=(Frame&&) = delete;

    ~Frame() final;

    void drawRectangle(const cc::Vector2f& pos, const cc::Vector2f& size, const cc::Color& color) override;

private:
    Renderer2d& m_renderer2d;

    Frame(Renderer2d&);
};


#endif //CYBERCRAFT_FRAME_H
