#ifndef CAMERA_HEADER
#define CAMERA_HEADER

#include <iostream>
#include <cmath>
#include "const.hpp"


struct Camera
{
    const large_float cameraSpeed = CAMERA_SPEED;
    Vector2 position = Vector2::zero();
    large_float zoom = INITIAL_CAMERA_ZOOM;
    large_float zoomingSpeed = CAMERA_ZOOMING_SPEED;

    void Up(large_float dt) {
        position.y -= dt * cameraSpeed / zoom;
        #if DEBUG_MODE
            std::cout << "Going up" << std::endl;
            std::cout << "Camera position: " << position << std::endl;
        #endif
    }
    void Down(large_float dt) {
        position.y += dt * cameraSpeed / zoom;
        #if DEBUG_MODE
            std::cout << "Going down" << std::endl;
            std::cout << "Camera position: " << position << std::endl;
        #endif
    }
    void Right(large_float dt) {
        position.x += dt * cameraSpeed / zoom;
        #if DEBUG_MODE
            std::cout << "Going right" << std::endl;
            std::cout << "Camera position: " << position << std::endl;
        #endif
    }
    void Left(large_float dt) {
        position.x -= dt * cameraSpeed / zoom;
        #if DEBUG_MODE
            std::cout << "Going left" << std::endl;
            std::cout << "Camera position: " << position << std::endl;
        #endif
    }

    void ZoomOut(large_float dt) {
        large_float prevZoom = zoom;

        if (zoom > 1.0f) {
            zoom -= dt * zoomingSpeed / zoom;
        } else {
            zoom -= dt * zoomingSpeed * zoom;
        }

        zoom = std::max(MIN_CAMERA_ZOOM, zoom);

        #if DEBUG_MODE
            std::cout << "Zooming out" << std::endl;
            std::cout << "Zoom: " << zoom << std::endl;
        #endif
    }

    void ZoomIn(large_float dt) {
        large_float prevZoom = zoom;

        if (zoom > 1.0f) {
            zoom += dt * zoomingSpeed / zoom;
        } else {
            zoom += dt * zoomingSpeed * zoom;
        }

        zoom = std::min(MAX_CAMERA_ZOOM, zoom);

        #if DEBUG_MODE
            std::cout << "Zooming in" << std::endl;
            std::cout << "Zoom: " << zoom << std::endl;
        #endif
    }

};

#endif // CAMERA_HEADER