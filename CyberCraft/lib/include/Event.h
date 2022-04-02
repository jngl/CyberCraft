//
// Created by jngl on 18/03/2022.
//

#ifndef CYBERCRAFT_EVENT_H
#define CYBERCRAFT_EVENT_H

#include <variant>

namespace cc {
    struct QuitEvent{};
    struct KeyEvent{
        int key; // TODO
    };

    using Event = std::variant<QuitEvent,KeyEvent>;
}

#endif //CYBERCRAFT_EVENT_H
