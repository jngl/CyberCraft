//
// Created by jngl on 11/07/2021.
//

#include "SdlWindowAdapter.h"

#include <SDL.h>
#include <SDL2/SDL_syswm.h>

#include <bx/platform.h>

namespace cg::Impl {
    SdlWindowAdapter::SdlWindowAdapter(){
        if(SDL_Init(0) != 0){
            throw ck::GraphicsError{SDL_GetError()};
        }

        m_window = SDL_CreateWindow("OpenGL Test", 0, 0, windowSizeXDefault, windowSizeYDefault, SDL_WINDOW_RESIZABLE);
        if (m_window == nullptr) {
            throw ck::GraphicsError{SDL_GetError()};
        }
    }

    SdlWindowAdapter::~SdlWindowAdapter(){
        SDL_DestroyWindow(m_window);
        SDL_Quit();
    }

    SDL_Window* SdlWindowAdapter::GetSdlWindow(){
        return m_window;
    }

    void* SdlWindowAdapter::sdlNativeWindowHandle()
    {
        SDL_SysWMinfo wmi;
        SDL_VERSION(&wmi.version);
        if (!SDL_GetWindowWMInfo(m_window, &wmi) )
        {
            return NULL;
        }

#	if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
        #		if ENTRY_CONFIG_USE_WAYLAND
        wl_egl_window *win_impl = (wl_egl_window*)SDL_GetWindowData(_window, "wl_egl_window");
		if(!win_impl)
		{
			int width, height;
			SDL_GetWindowSize(_window, &width, &height);
			struct wl_surface* surface = wmi.info.wl.surface;
			if(!surface)
				return nullptr;
			win_impl = wl_egl_window_create(surface, width, height);
			SDL_SetWindowData(_window, "wl_egl_window", win_impl);
		}
		return (void*)(uintptr_t)win_impl;
#		else
        return reinterpret_cast<void*>(wmi.info.x11.window);
#		endif
#	elif BX_PLATFORM_OSX
        return wmi.info.cocoa.window;
#	elif BX_PLATFORM_WINDOWS
        return wmi.info.win.window;
#   else
        throw ck::GraphicsError("Unknown platform in MySdlWindow");
#	endif // BX_PLATFORM_
    }

    [[nodiscard]] cc::Vector2ui SdlWindowAdapter::getSize() const {
        int x = 1;
        int y = 1;
        SDL_GetWindowSize(m_window, &x, &y);
        return cc::Vector2ui{static_cast<uint>(x), static_cast<uint>(y)};
    }

    void SdlWindowAdapter::processEvent(ck::ExitListener &exitListener, ck::KeyListener &keyListener) {
        SDL_Event event;
        while (SDL_PollEvent(&event) != 0) {
            switch(event.type){
                case SDL_KEYDOWN:
                    keyListener.onKeyDown(keyFromSdlKey(event.key.keysym.sym));
                    break;
                case SDL_KEYUP:
                    keyListener.onKeyUp(keyFromSdlKey(event.key.keysym.sym));
                    break;
                case SDL_QUIT:
                    exitListener.onExit();
                    break;
                default:
                    break;
            }
        }
    }

    cp::Key SdlWindowAdapter::keyFromSdlKey(SDL_Keycode sdlKey) {
        switch (sdlKey){
            case SDLK_ESCAPE:
                return cp::Key::ESCAPE;
            case SDLK_UP:
                return cp::Key::UP;
            case SDLK_DOWN:
                return cp::Key::DOWN;
            case SDLK_LEFT:
                return cp::Key::LEFT;
            case SDLK_RIGHT:
                return cp::Key::RIGHT;
            case SDLK_F1:
                return cp::Key::F1;
            case SDLK_F2:
                return cp::Key::F2;
            case SDLK_F3:
                return cp::Key::F3;
            case SDLK_F4:
                return cp::Key::F4;
            case SDLK_F5:
                return cp::Key::F5;
            case SDLK_F6:
                return cp::Key::F6;
            case SDLK_F7:
                return cp::Key::F7;
            case SDLK_F8:
                return cp::Key::F8;
            case SDLK_F9:
                return cp::Key::F9;
            case SDLK_F10:
                return cp::Key::F10;
            case SDLK_F11:
                return cp::Key::F11;
            case SDLK_F12:
                return cp::Key::F12;
            default:
                return cp::Key::UNKNOWN;
        }
    }

    bool SdlWindowAdapter::isOpen() const {
        return true;
    }

    void SdlWindowAdapter::beginFrame() {
    }

    void SdlWindowAdapter::endFrame() {
    }

    bool SdlWindowAdapter::isKeyPressed(cp::Key) {
        return false;
    }
}
