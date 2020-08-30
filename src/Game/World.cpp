//
// Created by jngl on 25/08/2020.
//

#include "World.h"

World::World():
        m_blocs(){
    forEach([](int x, int y, Bloc& bloc){
        bloc = Bloc::Air;
    });
}

Bloc& World::getBloc(int x, int y) {
    return m_blocs[y*sizeX+x];
}

const Bloc &World::getBloc(int x, int y) const {
    return m_blocs[y*sizeX+x];
}


