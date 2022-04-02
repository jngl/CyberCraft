//
// Created by jngl on 05/03/2022.
//

#ifndef CYBERCRAFT_PLATFORM_H
#define CYBERCRAFT_PLATFORM_H

#include "Event.h"

#include <vector>

namespace cc {
    class Platform {
    public:
        virtual ~Platform() = default;

        virtual std::vector<Event> getEvents() = 0;

        virtual void draw() = 0;
    };
}

#endif //CYBERCRAFT_PLATFORM_H
