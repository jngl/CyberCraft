//
// Created by jngl on 27/06/2020.
//

#ifndef LIB_CYBERCRAFT_COMMON_H
#define LIB_CYBERCRAFT_COMMON_H

#include <string_view>

class Color;

class Window;

void printTabs(int nb);

using Uint8 = unsigned char;
using Uint32 = unsigned int;
static_assert(sizeof(Uint32) == 4, "size of Uint32 must be 32 bite");

class TextureHandle;


#endif //LIB_CYBERCRAFT_COMMON_H
