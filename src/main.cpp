#include "Main.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Event windowEvent;

    const char* error = nullptr;
    bool run = true;

    if (SDL_Init(SDL_INIT_VIDEO) != EXIT_SUCCESS) {
        cerr << "Failed to initialize SDL library: " << SDL_GetError() << endl;
        return EXIT_FAILURE;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        cerr << "Failed to initialize SDL_image: " << SDL_GetError() << endl;
        SDL_Quit();
        return EXIT_FAILURE;
    }

    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, CREATION_FLAGS);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!window) {
        cerr << "Failed to create window: " << SDL_GetError() << endl;
        return EXIT_FAILURE;
    }

    if (!renderer) {
        cerr << "Failed to get renderer: " << SDL_GetError() << endl;
        return EXIT_FAILURE;
    }

    vector<Planet> planets;
    bool paused = false;
    Random random((uint64_t)time(NULL));
    ScreenRender render(renderer, &planets);
    InputManager inputManager;

    /* Hard-coded demo */
    #if TEST_MODE
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

    // planets.push_back(photon);
    planets.push_back(humanLike);
    planets.push_back(earth);
    planets.push_back(moon); 
    planets.push_back(sun); 
    #endif
    /* this was for testing purposes */


    initializeClock();

    while (run) {
        #if DEBUG_MODE
        cout << "FPS: " << 1 / getDeltaTime() << endl;
        #endif

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
                    cout << "Spawned planet at position: " << (*planets.end()).position << "and mass " << (*planets.end()).mass << endl;
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
        // TODO: Figure out more sophisticated way
        /* Checking inputs */
        if (inputManager.GetKeyValue(MOVE_UPWARDS_KEY)) {
            render.camera.Up(getDeltaTime());
        }
        
        if (inputManager.GetKeyValue(MOVE_RIGHT_KEY)) {
            render.camera.Right(getDeltaTime());
        }

        if (inputManager.GetKeyValue(MOVE_LEFT_KEY)) {
            render.camera.Left(getDeltaTime());
        }
        
        if (inputManager.GetKeyValue(MOVE_DOWNWARDS_KEY)) {
            render.camera.Down(getDeltaTime());
        }
        
        if (inputManager.GetKeyValue(ZOOM_IN_KEY)) {
            render.camera.ZoomIn(getDeltaTime());
        }

        if (inputManager.GetKeyValue(ZOOM_OUT_KEY)) {
            render.camera.ZoomOut(getDeltaTime());
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
                cout << "Erased" << endl;
            #endif
            inputManager.ReleaseKey(DELETE_PLANETS_KEY);
        }
        if (inputManager.GetKeyValue(PAUSE_KEY)) {
            paused = !paused;
            #if DEBUG_MODE
            if (paused)
                cout << "Paused" << endl;
            else
                cout << "Started" << endl;
            #endif
            inputManager.ReleaseKey(PAUSE_KEY);
        }

        if (!paused) {
            for (size_t i = 0; i < planets.size(); ++i) {
                for (size_t j = i + 1; j < planets.size(); ++j) {
                    planets[i].DoPhysicsWithPlanet(&planets[j]);
                }
            }
            
            for (auto& planet : planets) {
                planet.setAcceleration();
                planet.Move(getDeltaTime());
            }
        }

        render.Render();

        tick();
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
