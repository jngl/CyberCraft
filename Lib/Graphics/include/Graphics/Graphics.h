//
// Created by jngl on 10/07/2021.
//

#ifndef CYBERCRAFT_GRAPHICS_H
#define CYBERCRAFT_GRAPHICS_H

#include <Ports.h>

#include <memory>

namespace cg{
    [[maybe_unused]] std::unique_ptr<cp::Ports> createGraphicsAdapter();
}

#endif //CYBERCRAFT_GRAPHICS_H
