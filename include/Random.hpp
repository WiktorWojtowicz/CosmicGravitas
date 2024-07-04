/*
    Custom LCG implementation
    Why?
    Just because
*/
#ifndef RANDOM_HEADER
#define RANDOM_HEADER

#include <stdint.h>
#include <limits>

struct Random {
    uint64_t seed;
    uint64_t aParam;
    uint64_t cParam;
    uint64_t mParam;
    Random(uint64_t s = 1, uint64_t a = 1103515425, uint64_t c = 12345, uint64_t m = UINT64_MAX): seed(s), aParam(a), cParam(c), mParam(m) 
    {
    }

    uint64_t random() {
        seed = (seed * aParam + cParam) % mParam;
        return (seed << 32);
    }

    int32_t randomInt() {
        return static_cast<int32_t>(random() % std::numeric_limits<int32_t>::max());
    }


    large_float randomLargeFloat() {
        return static_cast<large_float>(random());
    }

    int32_t mapIntToRange(int32_t value, int32_t a, int32_t b) {
        int32_t rangeSize = b - a;
        int32_t scaledValue = (value % rangeSize) + a;
        return scaledValue;
    }

    int32_t randomIntRange(int32_t a, int32_t b) {
        return mapIntToRange(randomInt(), a, b);
    }
};

#endif // RANDOM_HEADER