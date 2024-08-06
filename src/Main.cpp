#include "Main.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    Simulation sim;
    switch (sim.Init()) {
        case OK:
            break;
        case SDL_INIT_FAILURE:
            cout << "Failed to initialise SDL2" << endl;
            break;
        case VARIABLES_INIT_FALIURE:
            cout << "Failed to initialise variables" << endl;
            break;
        default:
            cout << "Failed to initialise simulation" << endl;
            return EXIT_FAILURE;
    }
    return sim.Run();
}
