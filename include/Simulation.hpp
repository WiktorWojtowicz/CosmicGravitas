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

    void HandleEvents() {
        while (SDL_PollEvent(&windowEvent)) {
            switch (windowEvent.type)
            {
                case SDL_QUIT: {
                    run = false;
                    break;
                }
                case SDL_MOUSEBUTTONDOWN: {
                    if (windowEvent.button.button == PLANET_SPAWN_BUTTON) {
                        int32_t spawnX, spawnY, randomMass;
                        SDL_GetMouseState(&spawnX, &spawnY);
                        randomMass = random.randomIntRange(MIN_PLANET_RANDOM_WEIGHT, MAX_PLANET_RANDOM_WEIGHT);

                        RGBA planetColor(
                            random.randomIntRange(0, 0xFF),
                            random.randomIntRange(0, 0xFF),
                            random.randomIntRange(0, 0xFF),
                            0xFF
                        );

                        // Create the planet
                        planets.emplace_back(
                            spawnX, 
                            spawnY, 
                            randomMass / 200, 
                            (static_cast<large_float> (randomMass)), 
                            planetColor,
                            &render.camera
                        );

                        #if DEBUG_MODE
                            std::cout << "Spawned planet at position: " << (*planets.end()).position << "and mass " << (*planets.end()).mass << std::endl;
                        #endif
                    }
                    break;
                }
                case SDL_KEYDOWN: {
                    inputManager.HandleKeyDown(windowEvent.key.keysym.sym);
                    break;
                }
                case SDL_KEYUP: {
                    inputManager.HandleKeyUp(windowEvent.key.keysym.sym);
                    break;
                }
                default:
                    break;
            }
        }
    }

    void ManageInput() {
        // TODO: Figure out more sophisticated way
        if (inputManager.GetKeyValue(MOVE_UPWARDS_KEY)) {
            render.camera.Up(clock.getDeltaTime());
        }
        
        if (inputManager.GetKeyValue(MOVE_RIGHT_KEY)) {
            render.camera.Right(clock.getDeltaTime());
        }

        if (inputManager.GetKeyValue(MOVE_LEFT_KEY)) {
            render.camera.Left(clock.getDeltaTime());
        }
        
        if (inputManager.GetKeyValue(MOVE_DOWNWARDS_KEY)) {
            render.camera.Down(clock.getDeltaTime());
        }
        
        if (inputManager.GetKeyValue(ZOOM_IN_KEY)) {
            render.camera.ZoomIn(clock.getDeltaTime());
        }

        if (inputManager.GetKeyValue(ZOOM_OUT_KEY)) {
            render.camera.ZoomOut(clock.getDeltaTime());
        }

        if (inputManager.GetKeyValue(SPRINT_KEY)) {
            render.camera.cameraSpeed = CAMERA_SPEED * CAMERA_SPRINT_MULTIPLIER;
        }
        else if (inputManager.GetKeyValue(SLOW_DOWN_KEY)) {
            render.camera.cameraSpeed = CAMERA_SPEED * CAMERA_SLOW_MULTIPLIER;
        } else {
            render.camera.cameraSpeed = CAMERA_SPEED;
        }

        if (inputManager.GetKeyValue(DELETE_PLANETS_KEY)) {
            planets.erase(planets.begin(), planets.end());
            #if DEBUG_MODE
                std::cout << "Erased" << std::endl;
            #endif
            inputManager.ReleaseKey(DELETE_PLANETS_KEY);
        }
        if (inputManager.GetKeyValue(PAUSE_KEY)) {
            paused = !paused;
            #if DEBUG_MODE
                if (paused)
                    std::cout << "Paused" << std::endl;
                else
                    std::cout << "Started" << std::endl;
            #endif
            inputManager.ReleaseKey(PAUSE_KEY);
        }
    }

    void CalculatePhysics() {
        for (size_t i = 0; i < planets.size(); ++i) {
            for (size_t j = i + 1; j < planets.size(); ++j) {
                planets[i].DoPhysicsWithPlanet(&planets[j]);
            }
        }
                
        for (auto& planet : planets) {
            planet.setAcceleration();
            planet.Move(clock.getDeltaTime());
        }
    }

    int RunMainThread() {
        while (run) {
            #if DEBUG_MODE
                std::cout << "FPS: " << 1 / clock.getDeltaTime() << std::endl;
            #endif

            HandleEvents();
            ManageInput();
            

            if (!paused) {
                CalculatePhysics();
            }

            render.Render();
            clock.tick();
        }
        return EXIT_SUCCESS;
    }

    int Run() {
        return RunMainThread();
    }

    bool InitialiseSDL() {
        if (SDL_Init(SDL_INIT_VIDEO) != EXIT_SUCCESS) {
            std::cerr << "Failed to initialize SDL library: " << SDL_GetError() << std::endl;
            return false;
        }

        if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
            std::cerr << "Failed to initialize SDL_image: " << SDL_GetError() << std::endl;
            SDL_Quit();
            return false;
        }

        window = SDL_CreateWindow(
            WINDOW_TITLE,
            SDL_WINDOWPOS_CENTERED, 
            SDL_WINDOWPOS_CENTERED,
            WINDOW_WIDTH, 
            WINDOW_HEIGHT, 
            CREATION_FLAGS
        );

        if (!window) {
            std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
            return false;
        }

        renderer = SDL_CreateRenderer(
            window, 
            -1, 
            SDL_RENDERER_ACCELERATED
        );

        if (!renderer) {
            std::cerr << "Failed to get renderer: " << SDL_GetError() << std::endl;
            return false;
        }
        return true;
    }

    bool InitialiseVariables() {
        /* Hard-coded demo */
        #if DEMO_MODE
        Planet sun(
            static_cast<large_float>(0),
            static_cast<large_float>(0),
            696340000,
            1989000000000000000000000000000.0f, 
            yellowColor, 
            &render.camera
        );

        Planet earth(
            static_cast<large_float>(149597870700),
            static_cast<large_float>(0),
            6371000, 
            5972190000000000000000000.0f, 
            greenColor, 
            &render.camera
        );
        earth.velocity.y = 30000.0f;
        
        Planet moon(
            static_cast<large_float>(earth.position.x + 384400000), 
            static_cast<large_float>(0),
            173700, 
            73476730900000000000000.0f, 
            whiteColor, 
            &render.camera
        );
        moon.velocity.y = earth.velocity.y + 1023.0f;
        
        Planet humanLike(
            static_cast<large_float>(earth.position.x),
            static_cast<large_float>(earth.position.y - earth.radius),
            static_cast<large_float>( 1 ),
            static_cast<large_float>( 80.0f ),
            redColor, 
            &render.camera
        );
        humanLike.velocity = earth.velocity;

        planets.push_back(humanLike);
        planets.push_back(earth);
        planets.push_back(moon); 
        planets.push_back(sun); 
        #endif

        clock.init();
        random = Random(((uint64_t)time(NULL)));
        render = ScreenRender(renderer, &planets);
        return true;
    }

    INIT_ERROR_CODE Init() {
        if (!InitialiseSDL())
            return SDL_INIT_FAILURE;
        if (!InitialiseVariables()) {
            return VARIABLES_INIT_FALIURE;
        }
        return OK;
    }

    ~Simulation() {
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
};


#endif // SIMULATION_HEADER