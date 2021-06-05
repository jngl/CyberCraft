//
// Created by jngl on 04/06/2021.
//

#include "MySdlWindow.h"

#include "Utils.h"

#include <SDL2/SDL_syswm.h>
#include <bx/platform.h>

MySdlWindow::MySdlWindow(){
    if(SDL_Init(0) != 0){
        throw SystemError{SDL_GetError()};
    }

    m_window = SDL_CreateWindow("OpenGL Test", 0, 0, windowSizeXDefault, windowSizeYDefault, SDL_WINDOW_RESIZABLE);
    if (m_window == nullptr) {
        throw SystemError{SDL_GetError()};
    }
}

MySdlWindow::~MySdlWindow(){
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

SDL_Window* MySdlWindow::GetSdlWindow(){
    return m_window;
}

void MySdlWindow::swap(){
    SDL_GL_SwapWindow(m_window);
}

void* MySdlWindow::sdlNativeWindowHandle()
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
    throw SystemError("Unknown platform in MySdlWindow");
#	endif // BX_PLATFORM_
}

[[nodiscard]] cc::Vector2ui MySdlWindow::getSize() const {
    int x = 1;
    int y = 1;
    SDL_GetWindowSize(m_window, &x, &y);
    return cc::Vector2ui{static_cast<uint>(x), static_cast<uint>(y)};
}
