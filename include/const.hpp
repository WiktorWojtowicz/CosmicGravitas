#ifndef CONST_HEADER
#define CONST_HEADER

#include <SDL.h>
#include <boost/multiprecision/cpp_dec_float.hpp>

#include "rgba.hpp"

using boost::multiprecision::cpp_dec_float_100;
typedef cpp_dec_float_100    large_float;

const char         WINDOW_TITLE[]   = "CosmicGravitas Alpha Window";
const unsigned int WINDOW_WIDTH     = 2560;
const unsigned int WINDOW_HEIGHT    = 1440;



const Uint32 CREATION_FLAGS         = SDL_WINDOW_SHOWN               |
                                    //   SDL_WINDOW_FULLSCREEN_DESKTOP  |
                                      SDL_WINDOW_BORDERLESS          |
                                      SDL_WINDOW_ALLOW_HIGHDPI;
                            

const large_float GRAVITATIONAL_CONSTANT = 0.000000000066743;
const large_float TIME_MULTIPLIER        = 1.0f;

/* Zooming and camera */
#define CAMERA_ZOOMING_SPEED        5.0f
#define INITIAL_CAMERA_ZOOM         0.000001f
#define CAMERA_SPEED                1000.0f
#define CAMERA_SPRINT_MULTIPLIER    1.5f
#define CAMERA_SLOW_MULTIPLIER      0.5f

const large_float MIN_CAMERA_ZOOM        = 0.0000000001f;
const large_float MAX_CAMERA_ZOOM        = 100000.0f;

/* Keys for movement and management of symulation */
#define MOVE_UPWARDS_KEY    SDLK_w
#define MOVE_RIGHT_KEY      SDLK_d
#define MOVE_LEFT_KEY       SDLK_a
#define MOVE_DOWNWARDS_KEY  SDLK_s
#define SPRINT_KEY          SDLK_LCTRL
#define SLOW_DOWN_KEY       SDLK_LSHIFT
#define ZOOM_IN_KEY         SDLK_e
#define ZOOM_OUT_KEY        SDLK_q
#define PAUSE_KEY           SDLK_SPACE
#define DELETE_PLANETS_KEY  SDLK_BACKSPACE

/* Values for beta functions */
#define MAX_PLANET_RANDOM_WEIGHT 1000000000
#define MIN_PLANET_RANDOM_WEIGHT 1000000

/* Random stuff*/
#define WINDOW_BORDER 0
#define PLANET_SPAWN_BUTTON SDL_BUTTON_LEFT
#define LARGE_PLANET_CONSTANT 6371000ll * 6371000ll / 1000ll

/* Colors*/
const RGBA redColor(255, 58, 104, 255);
const RGBA greenColor(110, 255, 105, 255);
const RGBA blueColor(79, 175, 255, 255);
const RGBA yellowColor(255, 228, 85, 255);
const RGBA blackColor(0, 0, 10, 255);
const RGBA whiteColor(255, 255, 255, 255);
const RGBA grayColor(130, 130, 130, 255);

#define BACKGROUND_COLOR blackColor

#define DEBUG_MODE false
#define DEMO_MODE  true

#endif // CONST_HEADER