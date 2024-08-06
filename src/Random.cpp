#include "Random.hpp"

Random::Random(uint64_t s, uint64_t a, uint64_t c, uint64_t m) : seed(s), aParam(a), cParam(c), mParam(m) 
{
}

uint64_t Random::random() {
    seed = (seed * aParam + cParam) % mParam;
    return (seed << 32);
}

int32_t Random::randomInt() {
    return static_cast<int32_t>(random() % std::numeric_limits<int32_t>::max());
}

large_float Random::randomLargeFloat() {
    return static_cast<large_float>(random());
}

int32_t Random::mapIntToRange(int32_t value, int32_t a, int32_t b) {
    int32_t rangeSize = b - a;
    int32_t scaledValue = (value % rangeSize) + a;
    return scaledValue;
}

int32_t Random::randomIntRange(int32_t a, int32_t b) {
    return mapIntToRange(randomInt(), a, b);
}
