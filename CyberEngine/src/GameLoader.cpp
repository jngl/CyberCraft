//
// Created by jngl on 05/06/2021.
//

#include "GameLoader.h"

#include <Core/Debug.h>
#include <Graphics/Graphics.h>

#include <iostream>

#include <SDL2/SDL.h>

GameLoader::GameLoader(){
    reload();
}

GameLoader::~GameLoader(){
    clear();
}

void GameLoader::reload(){
    std::cout<<"Reload"<<std::endl;

    clear();

    using Func = ck::GameBase*(*)();

    m_gameCodeHandle = SDL_LoadObject("./libDemo.so");
    if(m_gameCodeHandle == nullptr){
        throw GameLoaderError{SDL_GetError()};
    }

    Func creator = reinterpret_cast<Func>(SDL_LoadFunction(m_gameCodeHandle, "createGame")); // NOLINT
    if(creator == nullptr){
        throw cc::Error{SDL_GetError()};
    }

    m_game = std::unique_ptr<ck::GameBase>(creator());
}

ck::GameBase& GameLoader::getGame(){
    if(!m_game){
        throw cc::Error("Game not loaded");
    }
    return *m_game;
}

const ck::GameBase& GameLoader::getGame() const{
    if(!m_game){
        throw cc::Error("Game not loaded");
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
