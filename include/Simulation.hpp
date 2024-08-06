#ifndef SIMULATION_HEADER
#define SIMULATION_HEADER

#include <iostream>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <time.h>
#include <SDL.h>
#include <SDL_image.h>
#include <thread>
#include <mutex>
#include <condition_variable>

#include "Clock.hpp"
#include "Vector2.hpp"
#include "Planet.hpp"
#include "rgba.hpp"
#include "Random.hpp"
#include "const.hpp"
#include "ScreenRender.hpp"
#include "InputManager.hpp"

enum INIT_ERROR_CODE {
    OK,
    SDL_INIT_FAILURE,
    VARIABLES_INIT_FALIURE
};

struct Simulation
{
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Event windowEvent;

    std::vector<Planet> planets;
    bool paused = false;
    Random random;
    ScreenRender render;
    InputManager inputManager;

    Clock clock;

    const char* error = nullptr;
    bool run = true;

    void HandleEvents();
    void ManageInput();
    void CalculatePhysics();
    int RunMainThread();
    int Run();
    bool InitialiseSDL();
    bool InitialiseVariables();
    INIT_ERROR_CODE Init();

    ~Simulation();
};

#endif // SIMULATION_HEADER
