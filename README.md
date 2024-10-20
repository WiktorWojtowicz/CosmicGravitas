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

This is an alpha release. Many optimizations, fixes and overall improvements still need to be done to improve the user experience. Also screen size is not dynamic.

### Known Bugs 

- When a user zooms in too much, they may experience huge lags
- In case of a large time multiplier, small objects placed on large, massive objects may glitch

## Usage

To use Cosmic Gravitas you can either [build it from source](#building-from-source) or download the [compiled executable](https://github.com/WiktorWojtowicz/CosmicGravitas/releases/)

**Important note:** Since this is still an alpha release, there is no UI, so if you want to disable test planets, enable debug mode, speed up time or just chage keybinds, you need to do this in `include/const.hpp` and then [build it from source](#building-from-source)

- **Spawn Planets:** Click the mouse button to spawn a new planet at the cursor position with a random mass and color.
- **Control Camera:**
  - Move Up: Press `W`
  - Move Down: Press `S`
  - Move Left: Press `A`
  - Move Right: Press `D`
  - Zoom In: Hold `Q`
  - Zoom Out: Hold `E`
  - Sprint: Hold `Ctrl`
  - Slow Down: Hold `Shift`
- **Pause/Unpause Simulation:** Press `SPACE`
- **Delete All Planets:** Press `BACKSPACE`

## Building from Source

To build Cosmic Gravitas, you need to have SDL2, SDL_image and Boost libraries installed on your system. Follow the steps below to set up and run the program:

### Prerequisites

* **Tools**
    - CMake 3.30 or higher
    - C++17 or higher
    - At least one CMake kit
    - CPack (`Optional`)

* **Libraries**
    - Boost library
    - SDL2 library
    - SDL2_image library
---
**Important Note:** if you don't have these libraries CMake will attempt to fetch them. However fetching boost doesn't always work so keep that in mind


### Steps to build

1. **Clone the repository**

    ```bash
    git clone https://github.com/WiktorWojtowicz/CosmicGravitas
    cd CosmicGravitas
    ```

2. **Install libraries**

    - **On Linux (with apt):**

        ```bash
        sudo apt-get update && sudo apt upgrade -y && sudo apt-get install libsdl2-dev libsdl2-image-dev libboost-all-dev build-essential -y
        ```

    - **On macOS (using Homebrew):**

        ```bash
        brew install sdl2 sdl2_image boost
        ```

    - **On Windows:**

        Download the development libraries from the [SDL](https://github.com/libsdl-org/SDL/releases/tag/release-2.30.5), [SDL_image](https://github.com/libsdl-org/SDL_image/releases/tag/release-2.8.2) and [Boost](https://www.boost.org/users/download/) websites and follow the instructions for your development environment.

3. **Build the project**

    **Tip:** You can pass additional arguments to CMake (like -G) by simply passing them to build scripts

    - **On Linux:**

        ```bash
        chmod +x build-release.sh && ./build-release.sh -G "Unix Makefiles"
        ```

    - **On Windows:**
        ```bash
        .\build-release.bat -G "MinGW Makefiles"
        ```

4. **Install the program (`Optional`)**
    - **On Linux:**
        ```bash
        chmod +x install-release.sh && ./install-release.sh
        ```
    - **On Windows:**
        ```bash
        .\install-release.bat
        ```
5. **Done!**\
    Your binary should be in path/to/CosmicGravitas/build/release folder.
    Check [usage section](#usage) for more details about program

## Demo

The program includes demo setup that initializes a simple solar system with the Sun, Earth, Moon, and a human-like object. If you want to disable it, read [usage section](#usage).

## Contributing

Contributions are welcome! Please fork the repository and create a pull request with your improvements.

## License

Cosmic Gravitas is licensed under the MIT License. See the [LICENSE](LICENSE) file for more information.

## Contact

For any questions or suggestions, please open an issue on github!

---

Enjoy simulating the cosmos with Cosmic Gravitas!