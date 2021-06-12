//
// Created by jngl on 05/06/2021.
//

#include "Context.h"

#include "Frame.h"
#include "WindowSdl.h"

#include <iostream>
#include <SDL2/SDL_syswm.h>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

Context::Context(WindowSdl& win):
m_window(win){
        sdlSetWindow(win);

        m_size = win.getSize();

        bgfx::renderFrame();

        bgfx::Init init;
        init.type = bgfx::RendererType::OpenGL;
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

        m_renderer2d = std::make_unique<Renderer2d>();
}

Frame Context::beginFrame(){
    cc::Vector2ui  newSize = m_window.getSize();

    if(newSize.x != m_size.x || newSize.y != m_size.y){
        std::cout<<"resize "<<newSize.x<<" "<<newSize.y<<std::endl;
        bgfx::reset(newSize.x, newSize.y);
        m_size = newSize;
    }

    cc::Matrix4f proj;
    constexpr float dist = 100.f;
    proj.projectOrthographic(0, static_cast<float>(m_size.x), static_cast<float>(m_size.y), 0, -dist, dist);

    cc::Matrix4f view;

    m_renderer2d->setViewTransform(proj, view);

    bgfx::setViewRect(0, 0, 0, uint16_t(m_size.x), uint16_t(m_size.y) );
    bgfx::touch(0);

    bgfx::dbgTextClear();
    bgfx::dbgTextPrintf(0, 1, 0x0f, "win : %i %i", m_size.x, m_size.y);


    return Frame(*m_renderer2d);
}

bool Context::sdlSetWindow(WindowSdl& win)
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

GraphicsApi Context::getApi() const {
    switch (bgfx::getRendererType()){
        case bgfx::RendererType::Noop:
            return GraphicsApi::Noop;
        case bgfx::RendererType::Direct3D9:
            return GraphicsApi::Direct3D9;
        case bgfx::RendererType::Direct3D11:
            return GraphicsApi::Direct3D11;
        case bgfx::RendererType::Direct3D12:
            return GraphicsApi::Direct3D12;
        case bgfx::RendererType::Gnm:
            return GraphicsApi::Gnm;
        case bgfx::RendererType::Metal:
            return GraphicsApi::Metal;
        case bgfx::RendererType::Nvn:
            return GraphicsApi::Nvn;
        case bgfx::RendererType::OpenGL:
            return GraphicsApi::OpenGL;
        case bgfx::RendererType::OpenGLES:
            return GraphicsApi::OpenGLES;
        case bgfx::RendererType::Vulkan:
            return GraphicsApi::Vulkan;
        case bgfx::RendererType::WebGPU:
            return GraphicsApi::WebGPU;
        default:
            throw SystemError{"Unknown Graphics Api"};
    }
}
