//
// Created by jngl on 05/06/2021.
//

#ifndef CYBERCRAFT_GAMELOADER_H
#define CYBERCRAFT_GAMELOADER_H

<<<<<<< HEAD
#include <Kernel/Key.h>
#include <Kernel/Engine.h>
=======
#include <Core/Key.h>
#include <Core/Engine.h>
>>>>>>> b0d8808aab9721dbaa8c9afaf9c8a706f1faee8f

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

<<<<<<< HEAD
    ck::GameBase& getGame();

    [[nodiscard]] const ck::GameBase& getGame() const;
=======
    cc::GameBase& getGame();

    [[nodiscard]] const cc::GameBase& getGame() const;
>>>>>>> b0d8808aab9721dbaa8c9afaf9c8a706f1faee8f

    void processEvent();

private:
<<<<<<< HEAD
    std::unique_ptr<ck::GameBase> m_game;
=======
    std::unique_ptr<cc::GameBase> m_game;
>>>>>>> b0d8808aab9721dbaa8c9afaf9c8a706f1faee8f
    void* m_gameCodeHandle = nullptr;

    void processKeyUp(SDL_KeyboardEvent& keyEvent);
    void processKeyDown(SDL_KeyboardEvent& keyEvent);

};


#endif //CYBERCRAFT_GAMELOADER_H
