#ifndef CLOCK_HPP
#define CLOCK_HPP

#include <SDL.h>
#include "const.hpp"

struct Clock
{
    Uint64 lastCounter;
    large_float deltaTime;
    large_float secondsPerCount;

    void init();
    void tick();
    large_float getDeltaTime();
};


#endif // CLOCK_HPP
