#include "Clock.hpp"

void Clock::init() {
    Uint64 frequency = SDL_GetPerformanceFrequency();
    secondsPerCount = 1.0 / static_cast<cpp_dec_float_100>(frequency);
    lastCounter = SDL_GetPerformanceCounter();
}

void Clock::tick() {
    Uint64 currentCounter = SDL_GetPerformanceCounter();
    Uint64 countsElapsed = currentCounter - lastCounter;

    deltaTime = static_cast<large_float>(countsElapsed) * secondsPerCount;
    lastCounter = currentCounter;
}


large_float Clock::getDeltaTime() {
    return deltaTime;
}
