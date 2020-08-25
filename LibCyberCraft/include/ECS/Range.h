//
// Created by jngl on 08/08/2020.
//

#ifndef CYBERCRAFT_RANGE_H
#define CYBERCRAFT_RANGE_H

#include "Core/Common.h"
#include "Iterator.h"

#include <vector>

class Scene;

class Range{
public:
    explicit Range(Scene& scn, std::vector<Uint32>&& arrayId);

    Iterator begin();
    Iterator end();


private:
    std::vector<Uint32> m_arrayId;
    Scene& m_scene;
};

#endif //CYBERCRAFT_RANGE_H
