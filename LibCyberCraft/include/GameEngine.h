//
// Created by jngl on 02/09/2020.
//

#ifndef CYBERCRAFT_GAMEENIGNE_H
#define CYBERCRAFT_GAMEENIGNE_H

#include <memory>

#include <Core/Error.h>
#include <Core/Window.h>

class NoGameEngineError : Error{
public:
    NoGameEngineError();
};


class GameEngine {
public:
    static GameEngine& getInstance();

    GameEngine();

    virtual Window& getWindow() = 0;

private:
    static GameEngine* m_instance;
};

template<class WindowImpl>
class GameEngineImpl final : public GameEngine
{
public:
    Window& getWindow() override{
        return m_window;
    }

private:
    WindowImpl m_window;
};


#endif //CYBERCRAFT_GAMEENIGNE_H
