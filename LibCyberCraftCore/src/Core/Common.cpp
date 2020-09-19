//
// Created by jngl on 22/07/2020.
//
#include "Core/Common.h"

#include <iostream>

namespace ccCore {
    void printTabs(int nb) {
        for (int i = 0; i < nb; ++i) {
            std::cout << "\t";
        }
    }
}