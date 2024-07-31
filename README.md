# Cosmic Gravitas

Cosmic Gravitas is a 2D C++ program that uses Newton's law of gravity to simulate the movement of planets. This alpha release provides a basic implementation of the simulation, showcasing gravitational interactions and orbital dynamics.

## **Please note**

This is alpha release of my program that I made in my free time. Code quality will improve over time.

## Features

- Simulates gravitational forces between multiple celestial bodies
- Models realistic planetary motion based on Newtonian physics
- Handles collisions and updates velocities accordingly
- User interaction for spawning new planets and controlling the simulation

## Limitations

This is an alpha release. Many optimizations, fixes and overall improvements still need to be done to improve the user experience.

### Known Bugs 

- When a user zooms in too much, they may experience huge lags
- In case of a large time multiplier, small objects placed on large, massive objects may glitch


## Installation

To run Cosmic Gravitas, you need to have SDL2 and SDL_image libraries installed on your system. Follow the steps below to set up and run the program:

### Prerequisites

- C++17 or higher
- Boost 1.80 or higher
- CMake 3.20 or higher
- SDL2 library
- SDL2_image library

### Building from Source

1. **Clone the repository**

    ```bash
    git clone https://github.com/yourusername/cosmic-gravitas.git
    cd cosmic-gravitas
    ```

2. **Install SDL2 and SDL2_image**

    - **On Ubuntu:**

        ```bash
        sudo apt-get install libsdl2-dev libsdl2-image-dev
        ```

    - **On macOS (using Homebrew):**

        ```bash
        brew install sdl2 sdl2_image
        ```

    - **On Windows:**

        Download the development libraries from the [SDL](https://github.com/libsdl-org/SDL/releases/tag/release-2.30.5) and [SDL_image](https://github.com/libsdl-org/SDL_image/releases/tag/release-2.8.2) websites and follow the instructions for your development environment.

3. **Build the project**

    ```bash
    mkdir build
    cd build
    cmake ..
    make
    ```

4. **Run the program!**

    ```bash
    ./CosmicGravitas
    ```

## Usage
**Important note:** Since this is still an alpha release, there is no UI, so if you want to disable test planets, enable debug mode or speed up time, you need to do this in `include/const.hpp` and then [compile from source](#building-from-source)

- **Spawn Planets:** Click the mouse button to spawn a new planet at the cursor position with a random mass and color.
- **Control Camera:**
  - Move Up: Press `W`
  - Move Down: Press `S`
  - Move Left: Press `A`
  - Move Right: Press `D`
  - Zoom In: Press `Q`
  - Zoom Out: Press `E`
  - Sprint: Hold `Ctrl`
  - Slow Down: Hold `Shift`
- **Pause/Unpause Simulation:** Press `SPACE`
- **Delete All Planets:** Press `BACKSPACE`

## Demo

The program includes demo setup that initializes a simple solar system with the Sun, Earth, Moon, and a human-like object. To disable it read usage section.

## Contributing

Contributions are welcome! Please fork the repository and create a pull request with your improvements.

## License

Cosmic Gravitas is licensed under the MIT License. See the [LICENSE](LICENSE) file for more information.

## Contact

For any questions or suggestions, please open an issue on github!

---

Enjoy simulating the cosmos with Cosmic Gravitas!