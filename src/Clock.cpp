#include "Clock.hpp"

static Uint64 lastCounter = 0;
static large_float deltaTime = 0;
static large_float secondsPerCount = 0;

void initializeClock() {
    Uint64 frequency = SDL_GetPerformanceFrequency();
    secondsPerCount = 1.0 / static_cast<cpp_dec_float_100>(frequency);
    lastCounter = SDL_GetPerformanceCounter();
}

void tick() {
    Uint64 currentCounter = SDL_GetPerformanceCounter();
    Uint64 countsElapsed = currentCounter - lastCounter;

    deltaTime = static_cast<large_float>(countsElapsed) * secondsPerCount;
    lastCounter = currentCounter;
}


large_float getDeltaTime() {
    return deltaTime;
}
