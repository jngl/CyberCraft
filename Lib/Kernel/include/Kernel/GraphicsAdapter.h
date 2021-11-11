//
// Created by jngl on 11/11/2021.
//

#ifndef CYBERCRAFT_GRAPHICSADAPTER_H
#define CYBERCRAFT_GRAPHICSADAPTER_H

#include <memory>

#include <Core/Bases.h>

namespace ck
{
    class GraphicsAdapter : public cc::NonCopyable
    {
    public:
        virtual std::unique_ptr<ck::Frame> createFrame() = 0;
        virtual void processEvent(ck::ExitListener& exitListener, ck::KeyListener& keyListener) = 0;
    };
}

#endif //CYBERCRAFT_GRAPHICSADAPTER_H
