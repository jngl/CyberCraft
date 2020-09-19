//
// Created by jngl on 02/09/2020.
//

#include "GameEngine.h"

NoGameEngineError::NoGameEngineError(): Error("Game engine not found") {}

GameEngine* GameEngine::m_instance = nullptr;

GameEngine &GameEngine::getInstance() {
    if(m_instance == nullptr){
        throw NoGameEngineError();
    }

    return *m_instance;
}

GameEngine::GameEngine() {
    m_instance = this;
}



