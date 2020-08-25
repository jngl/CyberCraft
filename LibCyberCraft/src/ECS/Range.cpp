//
// Created by jngl on 08/08/2020.
//

#include "ECS/Range.h"

Range::Range(Scene& scn, std::vector<Uint32>&& arrayId):
m_arrayId(std::move(arrayId)),
m_scene(scn)
        {
        }

Iterator Range::begin(){
    return Iterator{};
}

Iterator Range::end(){
    return Iterator{};
}