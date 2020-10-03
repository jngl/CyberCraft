#include "Timer.hpp"

Timer::Timer():
mTimeStart(now())
{
}

float Timer::timeInSecond(){
    TimePoint t2 = now();
    Duration time_span = std::chrono::duration_cast<Duration>(t2 - mTimeStart);
    return time_span.count();
}

void Timer::restart(){
    mTimeStart = now();
}

Timer::TimePoint Timer::now(){
    return std::chrono::high_resolution_clock::now();
}
