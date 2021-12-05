//
// Created by jngl on 11/11/2021.
//

#ifndef CYBERCRAFT_PORTS_H
#define CYBERCRAFT_PORTS_H

#include <Core/Bases.h>

#include <Ports/GpuAdapter.h>
#include <Ports/Window.h>

namespace cp
{
    void foo();

    class Ports : cc::NonCopyable
    {
    public:
        virtual GpuAdapter& getGpuAdapter() = 0;
        virtual Window& getWindow() = 0;
    };
}

#endif //CYBERCRAFT_PORTS_H
