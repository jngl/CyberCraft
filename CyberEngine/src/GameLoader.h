//
// Created by jngl on 05/06/2021.
//

#ifndef CYBERCRAFT_GAMELOADER_H
#define CYBERCRAFT_GAMELOADER_H

#include <Core/Bases.h>

#include <Kernel/Key.h>
#include <Kernel/Engine.h>

#include <memory>

class GameLoaderError : public std::exception
{
public:
    explicit GameLoaderError(std::string_view msg);

    [[nodiscard]] const char* what() const noexcept override;
private:
    std::string m_message;
};

class GameLoader final : cc::NonCopyable
{
public:
    GameLoader();
    ~GameLoader();

    void reload();
    void clear();

    ck::GameBase& getGame();

    [[nodiscard]] const ck::GameBase& getGame() const;

private:
    std::unique_ptr<ck::GameBase> m_game;
    void* m_gameCodeHandle = nullptr;

};


#endif //CYBERCRAFT_GAMELOADER_H
