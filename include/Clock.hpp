#ifndef CLOCK_HPP
#define CLOCK_HPP

#include <SDL.h>
#include "const.hpp"

void initializeClock();
void tick();
large_float getDeltaTime();

#endif // CLOCK_HPP
