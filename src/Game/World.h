//
// Created by jngl on 25/08/2020.
//

#ifndef CYBERCRAFT_WORLD_H
#define CYBERCRAFT_WORLD_H

#include "Bloc.h"

#include <array>

class World {
public:
    static constexpr int sizeX = 16;
    static constexpr int sizeY = 16;

    constexpr World():
    m_blocs(){
        forEach([](int x, int y, Bloc& bloc){
            bloc = Bloc::Air;
        });
    }

    constexpr Bloc& getBloc(int x, int y){
        return m_blocs[y*sizeX+x];
    }

    [[nodiscard]] constexpr const Bloc& getBloc(int x, int y) const {
        return m_blocs[y*sizeX+x];
    }

    template<class Func>
    constexpr void forEach(Func f){
        for(int y(0); y<World::sizeY; ++y) {
            for (int x(0); x < World::sizeX; ++x) {
                f(x, y, getBloc(x, y));
            }
        }
    }

private:
    std::array<Bloc, sizeX*sizeY> m_blocs;
};

#endif //CYBERCRAFT_WORLD_H
