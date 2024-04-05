#include <chrono>
#include <iostream>
#include "timer.hpp"

Timer::Timer(bool log, const char* appender) {
    strAppender = appender;
    shouldLog = log;
}

void Timer::start() {
    startPos = std::chrono::high_resolution_clock::now();
}
void Timer::end() {
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - startPos);
    if (shouldLog) {
        std::cout << strAppender << duration.count() << std::endl;
    }
}