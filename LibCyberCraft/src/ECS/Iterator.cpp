//
// Created by jngl on 08/08/2020.
//

#include "ECS/Iterator.h"

bool Iterator::operator!=(const Iterator& range) {
    return false;
}

const Iterator& Iterator::operator++() {
    return *this;
}

template<class T>
T& Iterator::get(){
    return 0;
}

Iterator& Iterator::operator*(){
    return *this;
}