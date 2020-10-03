#pragma once

#include <chrono>

namespace ccCore {
    class Timer {
    public:
        Timer();

        float timeInSecond();

        void restart();

    private:
        typedef std::chrono::high_resolution_clock::time_point TimePoint;
        typedef std::chrono::duration<float> Duration;

        TimePoint mTimeStart;

        static TimePoint now();
    };
}