//
// Created by jngl on 19/02/2021.
//

#include "Core/Range.h"

namespace cc {
    const char *InvalidRange::what() const noexcept {
        return "Invalid Range";
    }
}
