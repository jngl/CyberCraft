//
// Created by jngl on 11/11/2021.
//

#ifndef CYBERCRAFT_KERNEL_H
#define CYBERCRAFT_KERNEL_H

#include "Renderer2d.h"

namespace ck
{
    class GraphicsAdapter;

    class Kernel
    {
    public:
        explicit Kernel(ck::GraphicsAdapter&);

        ck::Renderer2d& getRenderer2d();


        void nextFrame();

    private:
        ck::GraphicsAdapter& m_graphicsAdapter;
        ck::Renderer2d m_renderer2d;

        void beginFrame();
    };
}

#endif //CYBERCRAFT_KERNEL_H
