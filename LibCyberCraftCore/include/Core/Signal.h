//
// Created by jngl on 12/09/2020.
//

#ifndef CYBERCRAFT_SIGNAL_H
#define CYBERCRAFT_SIGNAL_H

#include <vector>
#include <functional>
#include <iostream>

namespace cc {

    template<class ...Args>
    class Signal {
    public:
        using Func = std::function<void(Args...)>;

        void connect(Func func) {
            m_functions.push_back(func);
        }

    protected:
        std::vector<Func> m_functions;
    };

    template<class ...Args>
    class SignalEmitter : public Signal<Args...> {
    public:
        using Func = typename Signal<Args...>::Func;

        void emit(Args... args) {
            for (Func &f: Signal<Args...>::m_functions) {
                f(args...);
            }
        }
    };

}

#endif //CYBERCRAFT_SIGNAL_H
