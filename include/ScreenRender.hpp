#ifndef RENDER_HPP
#define RENDER_HPP

#include <iostream>
#include <vector>
#include <SDL.h>
#include <stdint.h>

#include "Planet.hpp"
#include "const.hpp"
#include "Camera.hpp"

struct ScreenRender {
    SDL_Renderer* renderer;
    std::vector<Planet>* planets;
    Camera camera;

    ScreenRender();
    ScreenRender(SDL_Renderer* r, std::vector<Planet>* pl);

    void ClearRender();
    void RenderFillCircle(int64_t x, int64_t y, int64_t radius);
    bool OnScreen(Planet* p);
    void RenderPlanet(Planet* p);
    void RenderFrame();
    void SwapBuffers();
    void Render();
};

#endif // RENDER_HPP
