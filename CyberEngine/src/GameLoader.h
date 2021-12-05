//
// Created by jngl on 05/06/2021.
//

#ifndef CYBERCRAFT_GAMELOADER_H
#define CYBERCRAFT_GAMELOADER_H

#include <Core/Bases.h>

#include <Ports/Key.h>
#include <Kernel/Game.h>

#include <memory>
#include <string>

namespace cp
{
    class Ports;
}

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
    GameLoader(cp::Ports&);
    ~GameLoader();

    void reload(cp::Ports&);
    void clear();

    ck::Game& getGame();

    [[nodiscard]] const ck::Game& getGame() const;

private:
    std::unique_ptr<ck::Game> m_game;
    void* m_gameCodeHandle = nullptr;

};


#endif //CYBERCRAFT_GAMELOADER_H
