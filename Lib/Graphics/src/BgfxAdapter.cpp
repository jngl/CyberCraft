//
// Created by jngl on 11/07/2021.
//

#include "BgfxAdapter.h"

#include "SdlWindowAdapter.h"

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

#include <SDL.h>
#include <SDL2/SDL_syswm.h>

#include <iostream>

namespace cg::Impl {

    BgfxAdapter::BgfxAdapter(SdlWindowAdapter& win){
        sdlSetWindow(win);

        m_size = win.getSize();

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

    void BgfxAdapter::beginFrame(cc::Vector2ui newSize){
        if(newSize.x != m_size.x || newSize.y != m_size.y){
            std::cout<<"resize "<<newSize.x<<" "<<newSize.y<<std::endl;
            bgfx::reset(newSize.x, newSize.y);
            m_size = newSize;
        }

        bgfx::setViewRect(0, 0, 0, uint16_t(m_size.x), uint16_t(m_size.y) );
        bgfx::touch(0);

        bgfx::dbgTextClear();
        bgfx::dbgTextPrintf(0, 1, 0x0f, "win : %i %i", m_size.x, m_size.y);
    }

    bool BgfxAdapter::sdlSetWindow(SdlWindowAdapter& win)
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

    ck::GraphicsApi BgfxAdapter::getApi() const {
        switch (bgfx::getRendererType()){
            case bgfx::RendererType::Noop:
                return ck::GraphicsApi::Noop;
            case bgfx::RendererType::Direct3D9:
                return ck::GraphicsApi::Direct3D9;
            case bgfx::RendererType::Direct3D11:
                return ck::GraphicsApi::Direct3D11;
            case bgfx::RendererType::Direct3D12:
                return ck::GraphicsApi::Direct3D12;
            case bgfx::RendererType::Gnm:
                return ck::GraphicsApi::Gnm;
            case bgfx::RendererType::Metal:
                return ck::GraphicsApi::Metal;
            case bgfx::RendererType::Nvn:
                return ck::GraphicsApi::Nvn;
            case bgfx::RendererType::OpenGL:
                return ck::GraphicsApi::OpenGL;
            case bgfx::RendererType::OpenGLES:
                return ck::GraphicsApi::OpenGLES;
            case bgfx::RendererType::Vulkan:
                return ck::GraphicsApi::Vulkan;
            case bgfx::RendererType::WebGPU:
                return ck::GraphicsApi::WebGPU;
            default:
                throw ck::GraphicsError{"Unknown Graphics Api"};
        }
    }

    void BgfxAdapter::endFrame() {
        bgfx::frame();
    }
}