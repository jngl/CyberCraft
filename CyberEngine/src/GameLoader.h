//
// Created by jngl on 05/06/2021.
//

#ifndef CYBERCRAFT_GAMELOADER_H
#define CYBERCRAFT_GAMELOADER_H

#include <Core/Key.h>
#include <Core/Engine.h>

#include <memory>
#include <SDL2/SDL.h>

class GameLoader final
{
public:
    GameLoader();
    ~GameLoader();

    GameLoader(const GameLoader&) = delete;
    GameLoader(GameLoader&&) = delete;
    GameLoader& operator=(const GameLoader&) = delete;
    GameLoader& operator=(GameLoader&&) = delete;

    void reload();
    void clear();

    cc::GameBase& getGame();

    [[nodiscard]] const cc::GameBase& getGame() const;

    void processEvent();

private:
    std::unique_ptr<cc::GameBase> m_game;
    void* m_gameCodeHandle = nullptr;

    void processKeyUp(SDL_KeyboardEvent& keyEvent);
    void processKeyDown(SDL_KeyboardEvent& keyEvent);

};


#endif //CYBERCRAFT_GAMELOADER_H
