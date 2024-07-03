#ifndef INPUT_MANAGER_HEADER
#define INPUT_MANAGER_HEADER

#include <SDL.h>
#include <vector>
#include <unordered_map>

// TODO: handle mouse events

struct InputManager
{
    std::unordered_map<SDL_Keycode, bool> keysPressed;

    InputManager()
    {
    }

    void HandleKeyUp(SDL_Keycode keyCode) {
        keysPressed[keyCode] = false;
    }
    void HandleKeyDown(SDL_Keycode keyCode) {
        keysPressed[keyCode] = true;
    }
    bool GetKeyValue(SDL_Keycode keyCode) {
        if (keysPressed.find(keyCode) != keysPressed.end()) {
            return keysPressed[keyCode];
        }
        return false;
    }
    void ReleaseKey(SDL_Keycode keyCode) {
        keysPressed[keyCode] = false;
    }
};


#endif // INPUT_MANAGER_HEADER