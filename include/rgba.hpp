#ifndef RGBA_HEADER
#define RGBA_HEADER

#include <stdint.h>

struct RGBA {
    int32_t R;
    int32_t G;
    int32_t B;
    int32_t A;
    
    RGBA(int32_t red, int32_t green, int32_t blue, int32_t alpha)
        : R(red), G(green), B(blue), A(alpha)
    {
    }
};

#endif // RGBA_HEADER