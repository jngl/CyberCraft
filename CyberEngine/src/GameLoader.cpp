//
// Created by jngl on 05/06/2021.
//

#include "GameLoader.h"

#include <Core/Debug.h>
#include <Graphics/Graphics.h>
#include <Ports.h>

#include <iostream>

#include <SDL2/SDL.h>

GameLoader::GameLoader(cp::Ports&ports){
    reload(ports);
}

GameLoader::~GameLoader(){
    clear();
}

void GameLoader::reload(cp::Ports& ports){
    std::cout<<"Reload"<<std::endl;

    clear();

    using Func = ck::Game*(*)(cp::Ports*);

    m_gameCodeHandle = SDL_LoadObject("./libDemo.so");
    if(m_gameCodeHandle == nullptr){
        throw GameLoaderError{SDL_GetError()};
    }

    Func creator = reinterpret_cast<Func>(SDL_LoadFunction(m_gameCodeHandle, "createGame")); // NOLINT
    if(creator == nullptr){
        throw cb::Error{SDL_GetError()};
    }

    m_game = std::unique_ptr<ck::Game>(creator(&ports));
}

ck::Game& GameLoader::getGame(){
    if(!m_game){
        throw cb::Error("Game not loaded");
    }
    return *m_game;
}

const ck::Game& GameLoader::getGame() const{
    if(!m_game){
        throw cb::Error("Game not loaded");
    }
    return *m_game;
}

void GameLoader::clear() {
    m_game.reset();
    if(m_gameCodeHandle != nullptr){
        SDL_UnloadObject(m_gameCodeHandle);
    }
}

GameLoaderError::GameLoaderError(std::string_view msg):
m_message(msg){

}

const char *GameLoaderError::what() const noexcept {
    return m_message.c_str();
}
