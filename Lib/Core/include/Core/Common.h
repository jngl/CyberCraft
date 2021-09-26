//
// Created by jngl on 27/06/2020.
//

#ifndef LIB_CYBERCRAFT_COMMON_H
#define LIB_CYBERCRAFT_COMMON_H

namespace cc {
    using Uint8 = unsigned char;
    using Uint16 = unsigned short;
    using Uint32 = unsigned int;
    using Uint64 = unsigned long;

    static_assert(sizeof(Uint8) == 1, "size of Uint8 must be 8 bite");
    static_assert(sizeof(Uint16) == 2, "size of Uint16 must be 16 bite");
    static_assert(sizeof(Uint32) == 4, "size of Uint32 must be 32 bite");
    static_assert(sizeof(Uint64) == 8, "size of Uint64 must be 64 bite");
}

#endif //LIB_CYBERCRAFT_COMMON_H
