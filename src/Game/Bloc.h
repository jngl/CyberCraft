//
// Created by jngl on 18/08/2020.
//

#ifndef CYBERCRAFT_BLOC_H
#define CYBERCRAFT_BLOC_H

#include "Component.h"

struct BlocInfo {
    component::Sprite sprite;
    bool collision = false;
};

enum class Bloc {
    Grass,
    Stone,
    Water,
    Air,
    Tree,
};

const BlocInfo& getBlocInfo(Bloc bloc);

#endif //CYBERCRAFT_BLOC_H
