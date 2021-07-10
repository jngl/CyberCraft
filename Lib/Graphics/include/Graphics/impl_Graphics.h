//
// Created by jngl on 10/07/2021.
//

#ifndef CYBERCRAFT_IMPL_GRAPHICS_H
#define CYBERCRAFT_IMPL_GRAPHICS_H

namespace cg{

    constexpr cc::Vector2f generateWindowViewSize(int windowX, int windowY){
        constexpr float minSize = 100;

        if(windowX > windowY){
            return {
                    minSize * static_cast<float>(windowX)  / static_cast<float>(windowY),
                    minSize
            };
        }

        return {
                minSize,
                minSize * static_cast<float>(windowY) / static_cast<float>(windowX)
        };
    }

    constexpr ck::Key keyFromSdlKey(SDL_Keycode sdlKey){
        switch (sdlKey){
            case SDLK_ESCAPE:
                return ck::Key::ESCAPE;
            case SDLK_UP:
                return ck::Key::UP;
            case SDLK_DOWN:
                return ck::Key::DOWN;
            case SDLK_LEFT:
                return ck::Key::LEFT;
            case SDLK_RIGHT:
                return ck::Key::RIGHT;
            case SDLK_F1:
                return ck::Key::F1;
            case SDLK_F2:
                return ck::Key::F2;
            case SDLK_F3:
                return ck::Key::F3;
            case SDLK_F4:
                return ck::Key::F4;
            case SDLK_F5:
                return ck::Key::F5;
            case SDLK_F6:
                return ck::Key::F6;
            case SDLK_F7:
                return ck::Key::F7;
            case SDLK_F8:
                return ck::Key::F8;
            case SDLK_F9:
                return ck::Key::F9;
            case SDLK_F10:
                return ck::Key::F10;
            case SDLK_F11:
                return ck::Key::F11;
            case SDLK_F12:
                return ck::Key::F12;
            default:
                return ck::Key::UNKNOWN;
        }
    }

    constexpr std::string_view GetGraphicsApiName(GraphicsApi api){
        switch (api) {
            case GraphicsApi::Noop:
                return "Noop";
            case GraphicsApi::Direct3D9:
                return "Direct3D9";
            case GraphicsApi::Direct3D11:
                return "Direct3D11";
            case GraphicsApi::Direct3D12:
                return "Direct3D12";
            case GraphicsApi::Gnm:
                return "Gnm";
            case GraphicsApi::Metal:
                return "Metal";
            case GraphicsApi::Nvn:
                return "Nvn";
            case GraphicsApi::OpenGLES:
                return "OpenGLES";
            case GraphicsApi::OpenGL:
                return "OpenGL";
            case GraphicsApi::Vulkan:
                return "Vulkan";
            case GraphicsApi::WebGPU:
                return "WebGPU";
        }
    }

    constexpr std::string_view GetGraphicsApiShaderType(GraphicsApi api){
        switch (api) {
            case GraphicsApi::Direct3D9:
                return "dx9";
            case GraphicsApi::Direct3D11:
            case GraphicsApi::Direct3D12:
                return "dx11";
            case GraphicsApi::Gnm:
                return "pssl";
            case GraphicsApi::Metal:
                return "metal";
            case GraphicsApi::Nvn:
                return "nvn";
            case GraphicsApi::OpenGLES:
                return "essl";
            case GraphicsApi::OpenGL:
                return "glsl";
            case GraphicsApi::Vulkan:
            case GraphicsApi::WebGPU:
                return "spirv";
            default:
                return "";
        }
    }

}

#endif //CYBERCRAFT_IMPL_GRAPHICS_H
