//
// Created by jngl on 05/06/2021.
//

#include "GameLoader.h"

#include "Utils.h"

#include <iostream>

GameLoader::GameLoader(){
    reload();
}

GameLoader::~GameLoader(){
    clear();
}

void GameLoader::reload(){
    std::cout<<"Reload"<<std::endl;

    clear();

<<<<<<< HEAD
    using Func = ck::GameBase*(*)();
=======
    using Func = cc::GameBase*(*)();
>>>>>>> b0d8808aab9721dbaa8c9afaf9c8a706f1faee8f

    m_gameCodeHandle = SDL_LoadObject("./libDemo.so");
    if(m_gameCodeHandle == nullptr){
        throw SystemError{SDL_GetError()};
    }

    Func creator = reinterpret_cast<Func>(SDL_LoadFunction(m_gameCodeHandle, "createGame")); // NOLINT
    if(creator == nullptr){
        throw SystemError{SDL_GetError()};
    }

<<<<<<< HEAD
    m_game = std::unique_ptr<ck::GameBase>(creator());
}

ck::GameBase& GameLoader::getGame(){
=======
    m_game = std::unique_ptr<cc::GameBase>(creator());
}

cc::GameBase& GameLoader::getGame(){
>>>>>>> b0d8808aab9721dbaa8c9afaf9c8a706f1faee8f
    if(!m_game){
        throw SystemError("Game not loaded");
    }
    return *m_game;
}

<<<<<<< HEAD
const ck::GameBase& GameLoader::getGame() const{
=======
const cc::GameBase& GameLoader::getGame() const{
>>>>>>> b0d8808aab9721dbaa8c9afaf9c8a706f1faee8f
    if(!m_game){
        throw SystemError("Game not loaded");
    }
    return *m_game;
}

void GameLoader::processEvent(){
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        switch(event.type){
            case SDL_KEYDOWN:
                processKeyDown(event.key);
                break;
            case SDL_KEYUP:
                processKeyUp(event.key);
                break;
            case SDL_QUIT:
                getGame().exit();
                break;
            default:
                break;
        }
    }
}

void GameLoader::processKeyUp(SDL_KeyboardEvent& keyEvent){
<<<<<<< HEAD
    ck::Key key = keyFromSdlKey(keyEvent.keysym.sym);
=======
    cc::Key key = keyFromSdlKey(keyEvent.keysym.sym);
>>>>>>> b0d8808aab9721dbaa8c9afaf9c8a706f1faee8f

    getGame().processKeyUp(key);
}

void GameLoader::processKeyDown(SDL_KeyboardEvent& keyEvent){
<<<<<<< HEAD
    ck::Key key = keyFromSdlKey(keyEvent.keysym.sym);

    if(key == ck::Key::F5){
=======
    cc::Key key = keyFromSdlKey(keyEvent.keysym.sym);

    if(key == cc::Key::F5){
>>>>>>> b0d8808aab9721dbaa8c9afaf9c8a706f1faee8f
        reload();
    }

    getGame().processKeyDown(key);
}

void GameLoader::clear() {
    m_game.reset();
    if(m_gameCodeHandle != nullptr){
        SDL_UnloadObject(m_gameCodeHandle);
    }
}
