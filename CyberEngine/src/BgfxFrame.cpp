//
// Created by jngl on 04/06/2021.
//

#include "BgfxFrame.h"

#include <bgfx/bgfx.h>

BgfxFrame::~BgfxFrame(){
    bgfx::frame();
}

void BgfxFrame::drawRectangle(const cc::Vector2f& pos, const cc::Vector2f& size, const cc::Color& color){
    bgfx::dbgTextPrintf(0, 0, 0x0f,
                        "rect : %.2f %.2f %.2f %.2f %i %i %i %i",
                        static_cast<double>(pos.x),
                        static_cast<double>(pos.y),
                        static_cast<double>(size.x),
                        static_cast<double>(size.y),
                        static_cast<int>(color.red),
                        static_cast<int>(color.green),
                        static_cast<int>(color.blue),
                        static_cast<int>(color.alpha));

//        cc::Vector2f size2 = size / 2.f;
//
//        glBegin(GL_QUADS);
//        glColor3ub(color.red, color.green, color.blue);
//        glVertex2f(pos.x + size2.x, pos.y + size2.y);
//        glVertex2f(pos.x + size2.x, pos.y - size2.y);
//        glVertex2f(pos.x - size2.x, pos.y - size2.y);
//        glVertex2f(pos.x - size2.x, pos.y + size2.y);
//        glEnd();
}
