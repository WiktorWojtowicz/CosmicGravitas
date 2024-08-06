#ifndef RENDER_HPP
#define RENDER_HPP

#include <iostream>
#include <vector>
#include <SDL.h>
#include <stdint.h>

#include "Planet.hpp"
#include "const.hpp"
#include "Camera.hpp"



struct ScreenRender
{
    SDL_Renderer*           renderer;
    std::vector<Planet>*    planets;
    Camera                  camera;

    ScreenRender() {} 


    ScreenRender(SDL_Renderer * r, std::vector<Planet> * pl): renderer(r), planets(pl) 
    {
    }

    void ClearRender() {
        SDL_SetRenderDrawColor(
            renderer,
            BACKGROUND_COLOR.R,
            BACKGROUND_COLOR.G,
            BACKGROUND_COLOR.B,
            BACKGROUND_COLOR.A
        );
        SDL_RenderClear(renderer);
    }

    void RenderFillCircle(int64_t x, int64_t y, int64_t radius) {
        int64_t offsetx, offsety, d;
        int64_t status;

        offsetx = 0;
        offsety = radius;
        d = radius - 1;
        status = 0;

        while (offsety >= offsetx) {
            if (y + offsetx > WINDOW_BORDER && y + offsetx < WINDOW_HEIGHT) {
                SDL_RenderDrawLine(
                    renderer, 
                    std::max(x - offsety, static_cast<int64_t>(WINDOW_BORDER - 1)), 
                    y + offsetx,
                    std::min(x + offsety, static_cast<int64_t>(WINDOW_WIDTH + 1)),
                    y + offsetx
                );
            }
           
            if (y - offsetx > WINDOW_BORDER && y - offsetx < WINDOW_HEIGHT) {
                SDL_RenderDrawLine(
                    renderer, 
                    std::max(x - offsety, static_cast<int64_t>(WINDOW_BORDER - 1)), 
                    y - offsetx, 
                    std::min(x + offsety, static_cast<int64_t>(WINDOW_WIDTH + 1)), 
                    y - offsetx
                );
            }
           

            if (y + offsety > WINDOW_BORDER && y + offsety < WINDOW_HEIGHT) {
                SDL_RenderDrawLine(
                    renderer, 
                    std::max(x - offsetx, static_cast<int64_t>(WINDOW_BORDER - 1)), 
                    y + offsety, 
                    std::min(x + offsetx, static_cast<int64_t>(WINDOW_WIDTH + 1)), 
                    y + offsety
                );
            }

            if (y - offsety > WINDOW_BORDER && y - offsety < WINDOW_HEIGHT) {
                SDL_RenderDrawLine(
                    renderer, 
                    std::max(x - offsetx, static_cast<int64_t>(WINDOW_BORDER - 1)), 
                    y - offsety, 
                    std::min(x + offsetx, static_cast<int64_t>(WINDOW_WIDTH + 1)), 
                    y - offsety
                );
            }

            if (d >= 2 * offsetx) {
                d -= 2 * offsetx + 1;
                offsetx += 1;
            } else if (d < 2 * (radius - offsety)) {
                d += 2 * offsety - 1;
                offsety -= 1;
            } else {
                d += 2 * (offsety - offsetx - 1);
                offsety -= 1;
                offsetx += 1;
            }
        }
    }
    
    bool OnScreen(Planet* p) {
        large_float screenPosX = (((p->position.x) - camera.position.x) * camera.zoom) + (static_cast<large_float>(WINDOW_WIDTH / 2));
        large_float screenPosY = (((p->position.y) - camera.position.y) * camera.zoom) + (static_cast<large_float>(WINDOW_HEIGHT / 2));
        large_float radius = (p->radius * camera.zoom);

        return (screenPosX + radius > 0 && screenPosX - radius < WINDOW_WIDTH &&
                screenPosY + radius > 0 && screenPosY - radius < WINDOW_HEIGHT);
    }


    void RenderPlanet(Planet* p) {
        int64_t screenPosX = (static_cast<int64_t>(((p->position.x) - camera.position.x) * camera.zoom)) + (static_cast<int64_t>(WINDOW_WIDTH / 2));
        int64_t screenPosY = (static_cast<int64_t>(((p->position.y) - camera.position.y) * camera.zoom)) + (static_cast<int64_t>(WINDOW_HEIGHT / 2));
        int64_t radius = static_cast<int64_t>(p->radius * camera.zoom);

        #if DEBUG_MODE
            std::cout << "Rendering position (x, y): (" << screenPosX << ", " << screenPosY << ")" << std::endl;
        #endif

        SDL_SetRenderDrawColor(renderer, p->color.R, p->color.G, p->color.B, p->color.A);
        RenderFillCircle(screenPosX, screenPosY, radius);
    }

    void RenderFrame() {
        for (int32_t i = 0; i < (*planets).size(); i++) {
            if (OnScreen(&((*planets)[i]))) {
                RenderPlanet(&((*planets)[i]));
            } 
            #if DEBUG_MODE
            else {
                std::cout << "Planet " << ((*planets)[i]).position << " is not on screen. Camera X and Y" << camera.position << ", Camera zoom: " << camera.zoom << std::endl;
            }
            #endif
        }
    }

    void SwapBuffers() {
        SDL_RenderPresent(renderer);
    }

    void Render() {
        ClearRender();
        RenderFrame();
        SwapBuffers();
    }

};
#endif // RENDER_HPP