//
// Created by jngl on 10/07/2021.
//

#ifndef CYBERCRAFT_GRAPHICS_H
#define CYBERCRAFT_GRAPHICS_H

#include <Kernel/Graphics.h>

#include <Kernel/GraphicsAdapter.h>

namespace cg{
    [[maybe_unused]] std::unique_ptr<ck::GraphicsAdapter> createGraphicsAdapter();
}

#endif //CYBERCRAFT_GRAPHICS_H
