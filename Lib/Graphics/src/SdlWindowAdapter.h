//
// Created by jngl on 11/07/2021.
//

#ifndef CYBERCRAFT_SDLWINDOWADAPTER_H
#define CYBERCRAFT_SDLWINDOWADAPTER_H

#include <Ports/Window.h>

#include <SDL2/SDL_scancode.h>

typedef int32_t SDL_Keycode;
struct SDL_Window;

namespace cc{
    template<class T>
    struct Vector2;
}

namespace cg::Impl{
class SdlWindowAdapter : public cp::Window{
    public:
        static constexpr int windowSizeXDefault = 1024;
        static constexpr int windowSizeYDefault = 768;

        SdlWindowAdapter();
        ~SdlWindowAdapter() override;

        SDL_Window* GetSdlWindow();

        void* sdlNativeWindowHandle();

        [[nodiscard]] cc::Vector2ui getSize() const override;

        [[nodiscard]] bool isOpen() const override;

        void beginFrame() override;

        void endFrame() override;

        bool isKeyPressed(cp::Key key) override;

    private:
        SDL_Window *m_window;

        cp::Key keyFromSdlKey(SDL_Keycode sdlKey);
        SDL_Scancode sdlScanCodeFromKey(cp::Key);
    };
}

#endif //CYBERCRAFT_SDLWINDOWADAPTER_H
