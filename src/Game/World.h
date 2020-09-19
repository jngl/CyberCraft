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
        forEach([](int x, int y, const BlocInfo*& bloc){
            bloc = nullptr;
        });
    }

    constexpr const BlocInfo*& getBloc(int x, int y){
        if(x<0 || x>=sizeX || y<0 || y>=sizeY){
            throw ccCore::Error("out of bound");
        }
        return m_blocs[y*sizeX+x];
    }

    [[nodiscard]] constexpr const BlocInfo* getBloc(int x, int y) const {
        if(x<0 || x>=sizeX || y<0 || y>=sizeY){
            throw ccCore::Error("out of bound");
        }
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

    [[nodiscard]] constexpr bool isInGroup(int x, int y, const BlocGroup& group) const{
        if(x<0 || x>=World::sizeX || y<0 || y>=World::sizeY){
            return false;
        }

        auto bloc = getBloc(x, y);

        if(!bloc){
            return false;
        }

        return &bloc->group == &group;
    }

    [[nodiscard]] constexpr bool isNeighbourInGroup(int x, int y, const BlocGroup& group) const {
        return isInGroup(x-1, y, group) ||
               isInGroup(x+1, y, group) ||
               isInGroup(x, y-1, group) ||
               isInGroup(x, y+1, group);
    }

    int numberOfNeighbourInGroup(int x, int y, const BlocGroup& group) const {
        int count = 0;

        if(isInGroup(x-1, y, group)) ++count;
        if(isInGroup(x+1, y, group)) ++count;
        if(isInGroup(x, y-1, group)) ++count;
        if(isInGroup(x, y+1, group)) ++count;

        return count;
    }

private:
    std::array<const BlocInfo*, sizeX*sizeY> m_blocs;
};

#endif //CYBERCRAFT_WORLD_H
