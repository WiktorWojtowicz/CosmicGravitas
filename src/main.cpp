#include "main.hpp"

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

    /* this is for testing purposes */
    #if TEST_MODE    
    RGBA redColor(255, 58, 104, 255);
    RGBA greenColor(110, 255, 105, 255);
    RGBA blueColor(79, 175, 255, 255);

    Planet testPlanetA(renderer, WINDOW_BORDER, WINDOW_HEIGHT / 2, 10, 10000, blueColor);
    Planet testPlanetB(renderer, WINDOW_WIDTH - WINDOW_BORDER, WINDOW_HEIGHT / 2, 20, 20000, greenColor);
    Planet testPlanetC(renderer, 0, 0, 5, 5000, redColor);

    planets.push_back(testPlanetA);
    planets.push_back(testPlanetB); 
    for (int i = 0; i < 5; i++) {
        planets.push_back(testPlanetC);
        testPlanetC.position.y += 300 * SCALING_VALUE;
        testPlanetC.position.x += 600 * SCALING_VALUE;
    }
    #endif
    /* this was for testing purposes */
    Random random((uint64_t)time(NULL));

    initializeClock();

    while (run) {
        while (SDL_PollEvent(&windowEvent)) {
            switch (windowEvent.type)
            {
            case SDL_QUIT: {
                run = false;
                break;
            }
            case SDL_KEYDOWN: {
                switch (windowEvent.key.keysym.sym) {
                    case SDLK_SPACE: {
                        int32_t spawnX, spawnY, weight;
                        weight = random.randomIntRange(MIN_PLANET_RANDOM_WEIGHT, MAX_PLANET_RANDOM_WEIGHT);
                        SDL_GetMouseState(&spawnX, &spawnY);

                        RGBA planetToSpawnColor(
                            random.randomIntRange(0, 0xFF),
                            random.randomIntRange(0, 0xFF),
                            random.randomIntRange(0, 0xFF),
                            random.randomIntRange(0, 0xFF)
                        );
                        
                        Planet planetToSpawn(
                            renderer,
                            spawnX,
                            spawnY,
                            weight / 200,
                            weight,
                            planetToSpawnColor
                        );

                        planets.push_back(planetToSpawn);
                        #if DEBUG_MODE
                        cout << "Spawned planet: " << planetToSpawn.position << endl;
                        #endif
                        break;
                    }
                    case SDLK_BACKSPACE: {
                        planets.erase(planets.begin(), planets.end());
                        #if DEBUG_MODE
                        cout << "Erased" << endl;
                        #endif
                    }
                    default:
                        break;
                    }
                break;
                }
            default:
                break;
            }

        }

        for (size_t i = 0; i < planets.size(); ++i) {
            for (size_t j = i + 1; j < planets.size(); ++j) {
                planets[i].DoPhysicsWithPlanet(&planets[j]);
            }
        }
        
        for (auto& planet : planets) {
            planet.setAcceleration();
            planet.Move(getDeltaTime());
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        for (auto& planet : planets) {
            planet.Draw();
        }

        SDL_RenderPresent(renderer);
        tick();
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
