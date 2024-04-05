#include <chrono>
#include <iostream>
#include "timer.hpp"

Timer::Timer(bool log, const char *appender, bool autoStart)
{
    strAppender = appender;
    shouldLog = log;
    if (autoStart) {
        start();
    }
}

void Timer::start()
{
    startPos = std::chrono::high_resolution_clock::now();
}
void Timer::end()
{
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - startPos);
    if (shouldLog)
    {
        std::cout << strAppender << duration.count() << " ticks. " << std::endl;
    }
}