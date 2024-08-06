/*
    Custom LCG implementation
    Why?
    Just because
*/
#ifndef RANDOM_HEADER
#define RANDOM_HEADER

#include <stdint.h>
#include <limits>
#include "const.hpp" // Assuming large_float is defined in const.hpp

class Random {
public:
    uint64_t seed;
    uint64_t aParam;
    uint64_t cParam;
    uint64_t mParam;

    Random(uint64_t s = 1, uint64_t a = 1103515425, uint64_t c = 12345, uint64_t m = UINT64_MAX);

    uint64_t random();
    int32_t randomInt();
    large_float randomLargeFloat();
    int32_t mapIntToRange(int32_t value, int32_t a, int32_t b);
    int32_t randomIntRange(int32_t a, int32_t b);
};

#endif // RANDOM_HEADER
