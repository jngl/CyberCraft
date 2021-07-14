//
// Created by jngl on 08/05/2021.
//

#ifndef CYBERCRAFT_ENGINE_H
#define CYBERCRAFT_ENGINE_H

#include "Key.h"
#include "Engine2D.h"

#include <Core/Math.h>

#include <memory>
#include <unordered_map>
#include <set>

namespace ck
{
    class Command
    {
    public:
        Command() = default;
        Command(const Command&) = default;
        Command(Command&&) = default;
        Command& operator=(const Command&) = default;
        Command& operator=(Command&&) = default;

        virtual ~Command() = default;

        virtual void exec() = 0;
    };

    class Runnable
    {
    public:
        Runnable() = default;
        Runnable(const Runnable&) = default;
        Runnable(Runnable&&) = default;
        Runnable& operator=(const Runnable&) = default;
        Runnable& operator=(Runnable&&) = default;

        virtual ~Runnable() = default;

        void exit(){
            m_running = false;
        }

        [[nodiscard]] bool isRunning() const {
            return m_running;
        }

    private:
        bool m_running = true;
    };

    class GameBase : public Runnable
    {
    public:


        virtual void render(ck::ColoredRectangleDrawer& renderer) = 0;

        void updateMultiFrameAction(){
            for(Command* cmd: m_currentMulti){
                if(cmd != nullptr){
                    cmd->exec();
                }
            }
        }

        void processKeyDown(ck::Key key){
            const auto itOne = m_oneFrameAction.find(key);
            if(itOne != std::end(m_oneFrameAction)){
                itOne->second->exec();
            }

            const auto itMulti = m_multiFrameAction.find(key);
            if(itMulti != std::end(m_multiFrameAction)){
                Command* cmd = itMulti->second.get();
                m_currentMulti.insert(cmd);
            }
        }

        void processKeyUp(ck::Key key){
            const auto itMulti = m_multiFrameAction.find(key);
            if(itMulti != std::end(m_multiFrameAction)){
                Command* cmd = itMulti->second.get();
                m_currentMulti.erase(cmd);
            }
        }

    protected:
        void createOneFrameAction(std::unique_ptr<Command> command, ck::Key defaultKey){
            m_oneFrameAction.insert({defaultKey, std::move(command)});
        }

        void createMultiFrameAction(std::unique_ptr<Command> command, ck::Key defaultKey){
            m_multiFrameAction.insert({defaultKey, std::move(command)});
        }

    private:
        std::unordered_map<ck::Key, std::unique_ptr<Command>> m_oneFrameAction;
        std::unordered_map<ck::Key, std::unique_ptr<Command>> m_multiFrameAction;
        std::set<Command*> m_currentMulti;
    };

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

#endif //CYBERCRAFT_ENGINE_H
