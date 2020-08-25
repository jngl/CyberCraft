//
// Created by jngl on 25/08/2020.
//

#include "World.h"

Bloc& World::getBloc(int x, int y) {
    return bloc[y*sizeX+x];
}

const Bloc &World::getBloc(int x, int y) const {
    return bloc[y*sizeX+x];
}
