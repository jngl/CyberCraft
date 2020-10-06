//
// Created by jngl on 03/10/2020.
//

#ifndef CYBERCRAFT_WINDOW_H
#define CYBERCRAFT_WINDOW_H

#include <Core/Window.h>

#include <SDL.h>
#include <map>
#include <functional>

class Window{
public:
    Window(int width, int height);
    ~Window();

    [[nodiscard]] bool isOpen() const;

    void beginFrame();
    void endFrame();

    void close();

    bool getSize(int* w, int* h);

    void addAction(SDL_Scancode key, bool* state, bool onPress);

    void clear();

private:
    struct Action{
        bool* state;
        bool onPress;
    };
    typedef std::map<SDL_Scancode, Action> ActionMap;


    bool mOpen;
    SDL_Window *mWindow;
    SDL_GLContext mGLContext;
    ActionMap mActions;
    bool mResize;

    void updateAction(SDL_Scancode key, bool press);
};

#endif //CYBERCRAFT_WINDOW_H
