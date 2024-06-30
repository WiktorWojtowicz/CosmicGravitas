#include "Clock.hpp"

static Uint32 lastTick;
static double deltaTime;

void initializeClock() {
    lastTick = SDL_GetTicks();
    deltaTime = 0.0;
}

void tick() {
    Uint32 currentTick = SDL_GetTicks();
    deltaTime = (currentTick - lastTick) / 1000.0;
    lastTick = currentTick;
}

double getDeltaTime() {
    return deltaTime;
}
