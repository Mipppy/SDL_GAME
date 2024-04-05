#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>

class Timer {
    public:
    bool shouldLog = false;
    const char* strAppender;
    std::chrono::high_resolution_clock::time_point startPos;
    Timer(bool log, const char* appender = "Timer: ");
    void start();
    void end();
};

#endif 