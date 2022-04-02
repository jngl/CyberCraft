//
// Created by jngl on 11/07/2021.
//

#ifndef CYBERCRAFT_SDLWINDOWADAPTER_H
#define CYBERCRAFT_SDLWINDOWADAPTER_H

struct SDL_Window;

#include <vector>

#include "Event.h"

namespace cc
{
    template<class T>
    struct Vector2;

    using Vector2ui = Vector2<unsigned int>;
}

namespace dp::impl
{
    class SdlWindow
    {
    public:
        static constexpr int windowSizeXDefault = 1024;
        static constexpr int windowSizeYDefault = 768;

        SdlWindow();

        ~SdlWindow();

        SDL_Window *GetSdlWindow();

        void *sdlNativeWindowHandle();

        [[nodiscard]] cc::Vector2ui getSize() const;

        std::vector<cc::Event> getEvents();

//        bool isKeyPressed(cp::Key key) override;

    private:
        SDL_Window *m_window;

//        cp::Key keyFromSdlKey(SDL_Keycode sdlKey);

//        SDL_Scancode sdlScanCodeFromKey(cp::Key);
    };
}

#endif //CYBERCRAFT_SDLWINDOWADAPTER_H
