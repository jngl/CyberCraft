//
// Created by jngl on 18/07/2020.
//

#ifndef CYBERCRAFT_UPDATE_H
#define CYBERCRAFT_UPDATE_H

#include <memory>
#include <chrono>

namespace ccCore {
    class FixStepUpdater {
    public:
        using clock = std::chrono::high_resolution_clock;
        using TimePoint = clock::time_point;
        using Duration = clock::duration;

        explicit FixStepUpdater(const Duration &timePerUpdate);

        template<class Callable>
        void update(Callable func) {
            TimePoint current = clock::now();
            Duration elapsed = current - m_previous;
            m_previous = current;
            m_lag += elapsed;

            while (m_lag >= m_timePerUpdate) {
                func();
                m_lag -= m_timePerUpdate;
            }
        }

    private:
        TimePoint m_previous;
        Duration m_lag;

        Duration m_timePerUpdate;
    };
}

#endif //CYBERCRAFT_UPDATE_H
