//
// Created by jngl on 11/07/2021.
//

#ifndef CYBERCRAFT_SDLWINDOWADAPTER_H
#define CYBERCRAFT_SDLWINDOWADAPTER_H

#include <Kernel/Graphics.h>
#include "BgfxAdapter.h"


typedef int32_t SDL_Keycode;
struct SDL_Window;

namespace cc{
    template<class T>
    struct Vector2;
}

namespace cg::Impl{
    class SdlWindowAdapter {
    public:
        static constexpr int windowSizeXDefault = 1024;
        static constexpr int windowSizeYDefault = 768;

        SdlWindowAdapter();
        ~SdlWindowAdapter();

        SDL_Window* GetSdlWindow();

        void swap();

        void* sdlNativeWindowHandle();

        [[nodiscard]] cc::Vector2ui getSize() const;

        void processEvent(ck::ExitListener& exitListener, ck::KeyListener& keyListener);

    private:
        SDL_Window *m_window;

        ck::Key keyFromSdlKey(SDL_Keycode sdlKey);
    };
}

#endif //CYBERCRAFT_SDLWINDOWADAPTER_H
