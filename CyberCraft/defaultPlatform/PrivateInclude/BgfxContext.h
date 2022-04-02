//
// Created by jngl on 02/04/2022.
//

#ifndef CYBERCRAFT_BGFXCONTEXT_H
#define CYBERCRAFT_BGFXCONTEXT_H

#include <CyberBase/Math.h>

namespace dp::impl {
    class SdlWindow;

    class BgfxContext {
    public:
        explicit BgfxContext(SdlWindow& window);

        void draw(cc::Vector2ui newSize);

    private:
        cc::Vector2ui m_size;

        void sdlSetWindow(SdlWindow& win);
    };
}

#endif //CYBERCRAFT_BGFXCONTEXT_H
