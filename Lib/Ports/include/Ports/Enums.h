//
// Created by jngl on 11/11/2021.
//

#ifndef CYBERCRAFT_ENUMS_H
#define CYBERCRAFT_ENUMS_H

#include <string_view>

namespace cp
{
    enum class GraphicsApi{
        Noop,         /// No rendering.
        Direct3D9,    /// Direct3D 9.0
        Direct3D11,   /// Direct3D 11.0
        Direct3D12,   /// Direct3D 12.0
        Gnm,          /// GNM
        Metal,        /// Metal
        Nvn,          /// NVN
        OpenGLES,     /// OpenGL ES 2.0+
        OpenGL,       /// OpenGL 2.1+
        Vulkan,       /// Vulkan
        WebGPU,       /// WebGPU
    };

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

#endif //CYBERCRAFT_ENUMS_H
