#ifndef CONST_HEADER
#define CONST_HEADER

const char         WINDOW_TITLE[]   = "CosmicGravitas Window";
const unsigned int WINDOW_WIDTH     = 2560 / 2;
const unsigned int WINDOW_HEIGHT    = 1440 / 2;


const Uint32 CREATION_FLAGS         = SDL_WINDOW_SHOWN               |
                                    //   SDL_WINDOW_FULLSCREEN_DESKTOP  |
                                      SDL_WINDOW_BORDERLESS          |
                                      SDL_WINDOW_ALLOW_HIGHDPI;
                            

// const double SCALING_VALUE          = 1.0f;
const double GRAVITATIONAL_CONSTANT = 0.000000000066743;
const double TIME_MULTIPLIER        = 1000000.0f;

#define CAMERA_ZOOMING_SPEED        1.0f;
#define INITIAL_CAMERA_ZOOM         1.0f;
#define CAMERA_SPEED                1000.0f;

/* Keys for movement and management of symulation */
#define MOVE_UPWARDS_KEY    SDLK_w
#define MOVE_RIGHT_KEY      SDLK_d
#define MOVE_LEFT_KEY       SDLK_a
#define MOVE_DOWNWARDS_KEY  SDLK_s
#define ZOOM_IN_KEY         SDLK_q
#define ZOOM_OUT_KEY        SDLK_e
#define PAUSE_KEY           SDLK_SPACE
#define DELETE_PLANETS_KEY  SDLK_BACKSPACE

/* Values for beta functions */
#define MAX_PLANET_RANDOM_WEIGHT 10000
#define MIN_PLANET_RANDOM_WEIGHT 100
#define WINDOW_BORDER 100
#define PLANET_SPAWN_BUTTON SDL_BUTTON_LEFT

const RGBA redColor(255, 58, 104, 255);
const RGBA greenColor(110, 255, 105, 255);
const RGBA blueColor(79, 175, 255, 255);
const RGBA blackColor(0, 0, 10, 255);
const RGBA whiteColor(255, 255, 255, 255);
const RGBA grayColor(130, 130, 130, 255);

#define BACKGROUND_COLOR blackColor

#define DEBUG_MODE false
#define TEST_MODE true

#endif // CONST_HEADER