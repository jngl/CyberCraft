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
}

#endif //CYBERCRAFT_ENGINE_H
