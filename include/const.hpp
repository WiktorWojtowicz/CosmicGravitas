#ifndef CONST_HEADER
#define CONST_HEADER

const char         WINDOW_TITLE[]   = "CosmicGravitas Window";
const unsigned int WINDOW_WIDTH     = 2560;
const unsigned int WINDOW_HEIGHT    = 1440;


const Uint32 CREATION_FLAGS         = SDL_WINDOW_SHOWN               |
                                      SDL_WINDOW_FULLSCREEN_DESKTOP  |
                                      SDL_WINDOW_BORDERLESS          |
                                      SDL_WINDOW_ALLOW_HIGHDPI;
                            

const double SCALING_VALUE          = 1.0f;
const double GRAVITATIONAL_CONSTANT = 0.000000000066743;
const double TIME_MULTIPLIER        = 1000000.0f;

/* Values for beta functions */
#define MAX_PLANET_RANDOM_WEIGHT 10000
#define MIN_PLANET_RANDOM_WEIGHT 100
#define WINDOW_BORDER 100


#define DEBUG_MODE false
#define TEST_MODE true

#endif // CONST_HEADER