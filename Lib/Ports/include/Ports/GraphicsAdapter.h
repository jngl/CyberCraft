//
// Created by jngl on 11/11/2021.
//

#ifndef CYBERCRAFT_GRAPHICSADAPTER_H
#define CYBERCRAFT_GRAPHICSADAPTER_H

#include <memory>

#include <Core/Bases.h>

namespace cp
{
    class GpuAdapter;
    class Window;

    class GraphicsAdapter : public cc::NonCopyable
    {
    public:
        virtual GpuAdapter& getGpuAdapter() = 0;
        virtual Window& getWindow() = 0;
    };
}

#endif //CYBERCRAFT_GRAPHICSADAPTER_H
