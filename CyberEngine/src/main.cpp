#include "TextureManager.h"

#include <Core/Engine.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <algorithm>
#include <iostream>

constexpr int windowSizeXDefault = 1024;
constexpr int windowSizeYDefault = 768;

cc::Key keyFromSdlKey(SDL_Keycode sdlKey){
    switch (sdlKey){
        case SDLK_ESCAPE:
            return cc::Key::ESCAPE;
        case SDLK_UP:
            return cc::Key::UP;
        case SDLK_DOWN:
            return cc::Key::DOWN;
        case SDLK_LEFT:
            return cc::Key::LEFT;
        case SDLK_RIGHT:
            return cc::Key::RIGHT;
        case SDLK_F1:
            return cc::Key::F1;
        case SDLK_F2:
            return cc::Key::F2;
        case SDLK_F3:
            return cc::Key::F3;
        case SDLK_F4:
            return cc::Key::F4;
        case SDLK_F5:
            return cc::Key::F5;
        case SDLK_F6:
            return cc::Key::F6;
        case SDLK_F7:
            return cc::Key::F7;
        case SDLK_F8:
            return cc::Key::F8;
        case SDLK_F9:
            return cc::Key::F9;
        case SDLK_F10:
            return cc::Key::F10;
        case SDLK_F11:
            return cc::Key::F11;
        case SDLK_F12:
            return cc::Key::F12;
        default:
            return cc::Key::UNKNOWN;
    }
}

void processKey(cc::GameBase& game, SDL_KeyboardEvent& keyEvent, bool& reload){
    cc::Key key = keyFromSdlKey(keyEvent.keysym.sym);
    if(keyEvent.type == SDL_KEYDOWN){
        if(key == cc::Key::F5){
            reload = true;
        }
        game.processKeyDown(key);
    }else if(keyEvent.type == SDL_KEYUP){
        game.processKeyUp(key);
    }
}

void processEvent(cc::GameBase& game, bool& reload){
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        switch(event.type){
            case SDL_KEYDOWN:
            case SDL_KEYUP:
                processKey(game, event.key, reload);
                break;
            case SDL_QUIT:
                game.exit();
                break;
            default:
                break;
        }
    }
}

cc::Vector2f generateWindowViewSize(int windowX, int windowY){
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

class OpenGlFrame final : public cc::ColoredRectangleDrawer, public cc::NonCopyable {
public:
    OpenGlFrame(int windowX, int windowY){
        glViewport(0, 0, windowX, windowY);
        glClearColor(0.f, 0.f, 0.f, 0.f);
        glClear(GL_COLOR_BUFFER_BIT);

        cc::Vector2f view = generateWindowViewSize(windowX, windowY);

        glPushMatrix();
        glOrtho(-view.x / 2.f, view.x / 2.f, -view.y/2.f, view.y/2.f, -1, 1);
    }

    ~OpenGlFrame() final{
        glPopMatrix();
    }

    void drawRectangle(const cc::Vector2f& pos, const cc::Vector2f& size, const cc::Color& color) override{
        cc::Vector2f size2 = size / 2.f;

        glBegin(GL_QUADS);
        glColor3ub(color.red, color.green, color.blue);
        glVertex2f(pos.x + size2.x, pos.y + size2.y);
        glVertex2f(pos.x + size2.x, pos.y - size2.y);
        glVertex2f(pos.x - size2.x, pos.y - size2.y);
        glVertex2f(pos.x - size2.x, pos.y + size2.y);
        glEnd();
    }
};

int main () {
    using Func = cc::GameBase*(*)();

    SDL_Window *window = SDL_CreateWindow("OpenGL Test", 0, 0, windowSizeXDefault, windowSizeYDefault, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (window == nullptr) {
        return 1;
    }

    SDL_GLContext Context = SDL_GL_CreateContext(window);

    TextureManager textures;

    void* handle = SDL_LoadObject("./libDemo.so");
    if(handle == nullptr){
        std::cout<<"Error : "<< SDL_GetError() <<std::endl;
        return 1;
    }

    Func creator = (Func)SDL_LoadFunction(handle, "createGame");
    if(creator == nullptr){
        std::cout<<"Error 2"<<std::endl;
        return 1;
    }

    std::unique_ptr<cc::GameBase> game = std::unique_ptr<cc::GameBase>(creator());

    while (game->isRunning()) {
        bool reload = false;

        processEvent(*game, reload);
        game->updateMultiFrameAction();

        if(reload){
            std::cout<<"Reload"<<std::endl;
            game.reset();

            SDL_UnloadObject(handle);

            handle = SDL_LoadObject("./libDemo.so");
            if(handle == nullptr){
                std::cout<<"Error : "<< SDL_GetError() <<std::endl;
                return 1;
            }

            creator = (Func)SDL_LoadFunction(handle, "createGame");
            if(creator == nullptr){
                std::cout<<"Error 2"<<std::endl;
                return 1;
            }

            game = std::unique_ptr<cc::GameBase>(creator());
        }

        int windowWidth = 1;
        int windowHeight = 1;
        SDL_GetWindowSize(window, &windowWidth, &windowHeight);

        { // Render
            OpenGlFrame renderer(windowWidth, windowHeight);
            game->render(renderer);
        }

        SDL_GL_SwapWindow(window);
    }

    SDL_UnloadObject(handle);
    SDL_GL_DeleteContext(Context);
    SDL_DestroyWindow(window);

    return 0;
}
