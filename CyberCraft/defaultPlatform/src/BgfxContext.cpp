//
// Created by jngl on 02/04/2022.
//

#include "BgfxContext.h"

#include "SdlWindow.h"

#include <CyberBase/Error.hpp>

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

#include <SDL2/SDL_syswm.h>

namespace dp::impl {
    BgfxContext::BgfxContext(SdlWindow& window) {
        sdlSetWindow(window);

        m_size = window.getSize();

        bgfx::renderFrame();

        bgfx::Init init;
        init.type = bgfx::RendererType::Vulkan;
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

    void BgfxContext::draw(cc::Vector2ui newSize) {
        if(newSize.x != m_size.x || newSize.y != m_size.y){
            bgfx::reset(newSize.x, newSize.y);
            m_size = newSize;
        }

        bgfx::setViewRect(0, 0, 0, uint16_t(m_size.x), uint16_t(m_size.y) );
        bgfx::touch(0);

        bgfx::dbgTextClear();

        bgfx::frame();
    }

    void BgfxContext::sdlSetWindow(SdlWindow &win) {
        SDL_SysWMinfo wmi;
        SDL_VERSION(&wmi.version);
        if (!SDL_GetWindowWMInfo(win.GetSdlWindow(), &wmi) )
        {
            throw cb::Error{"Internal error in BGFX context creation from SDL window"};
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

        pd.context      = nullptr;
        pd.backBuffer   = nullptr;
        pd.backBufferDS = nullptr;
        bgfx::setPlatformData(pd);
    }
}
