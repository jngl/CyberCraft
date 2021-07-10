//
// Created by jngl on 04/06/2021.
//

#ifndef CYBERCRAFT_BGFXFRAME_H
#define CYBERCRAFT_BGFXFRAME_H

#include <Kernel/Engine.h>

class BgfxFrame final : public ck::ColoredRectangleDrawer {
public:
    friend class MyBgfxContext;

    BgfxFrame(const BgfxFrame&) = delete;
    BgfxFrame(BgfxFrame&&) = delete;
    BgfxFrame& operator=(const BgfxFrame&) = delete;
    BgfxFrame& operator=(BgfxFrame&&) = delete;

    ~BgfxFrame() final;

    void drawRectangle(const cc::Vector2f& pos, const cc::Vector2f& size, const cc::Color& color) override;

private:
    BgfxFrame() = default;
};


#endif //CYBERCRAFT_BGFXFRAME_H
