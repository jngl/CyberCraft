#pragma once

#include <chrono>

namespace cc {
    class Timer {
    public:
        Timer();

        float timeInSecond();

        void restart();

    private:
        using TimePoint = std::chrono::high_resolution_clock::time_point;
        using Duration = std::chrono::duration<float>;

        TimePoint mTimeStart;

        static TimePoint now();
    };
}