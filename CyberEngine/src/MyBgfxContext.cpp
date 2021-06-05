//
// Created by jngl on 05/06/2021.
//

#include "MyBgfxContext.h"

#include "BgfxFrame.h"
#include "MySdlWindow.h"

#include <iostream>
#include <SDL2/SDL_syswm.h>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

MyBgfxContext::MyBgfxContext(MySdlWindow& win):
m_window(win){
        sdlSetWindow(win);

        m_size = win.getSize();

        bgfx::renderFrame();

        bgfx::Init init;
        //init.type = bgfx::RendererType::OpenGL;
        init.resolution.width  = m_size.x;
        init.resolution.height = m_size.y;
        bgfx::init(init);

        bgfx::setDebug(BGFX_DEBUG_TEXT);

        bgfx::setViewClear(0
        , BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH
        , 0x303030ff
        , 1.0f
        , 0
        );
}

BgfxFrame MyBgfxContext::beginFrame(){
    cc::Vector2i  newSize = m_window.getSize();

    if(newSize.x != m_size.x || newSize.y != m_size.y){
        std::cout<<"resize "<<newSize.x<<" "<<newSize.y<<std::endl;
        bgfx::reset((uint32_t)newSize.x, (uint32_t)newSize.y);
        m_size = newSize;
    }

    bgfx::setViewRect(0, 0, 0, uint16_t(m_size.x), uint16_t(m_size.y) );
    bgfx::touch(0);

    bgfx::dbgTextClear();
    bgfx::dbgTextPrintf(0, 1, 0x0f, "win : %i %i", m_size.x, m_size.y);


    return BgfxFrame();
}

bool MyBgfxContext::sdlSetWindow(MySdlWindow& win)
{
    SDL_SysWMinfo wmi;
    SDL_VERSION(&wmi.version);
    if (!SDL_GetWindowWMInfo(win.GetSdlWindow(), &wmi) )
    {
        return false;
    }

    bgfx::PlatformData pd;
#	if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
#		if ENTRY_CONFIG_USE_WAYLAND
    pd.ndt          = wmi.info.wl.display;
#		else
    pd.ndt          = wmi.info.x11.display;
#		endif
#	elif BX_PLATFORM_OSX
    pd.ndt          = NULL;
#	elif BX_PLATFORM_WINDOWS
        pd.ndt          = NULL;
#	endif // BX_PLATFORM_
    pd.nwh          = win.sdlNativeWindowHandle();

    pd.context      = NULL;
    pd.backBuffer   = NULL;
    pd.backBufferDS = NULL;
    bgfx::setPlatformData(pd);

    return true;
}