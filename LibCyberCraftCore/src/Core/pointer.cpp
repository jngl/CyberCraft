//
// Created by jngl on 03/12/2020.
//

#include "Core/pointer.h"

namespace cc {
    const char* NullPointerException::what() const noexcept {
        return "Null Pointer Exception";
    }
}