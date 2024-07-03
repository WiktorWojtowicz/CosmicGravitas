#ifndef CAMERA_HEADER
#define CAMERA_HEADER

#include <iostream>
#include "const.hpp"


struct Camera
{
    const double cameraSpeed = CAMERA_SPEED;
    Vector2 position = Vector2::zero();
    double zoom = INITIAL_CAMERA_ZOOM;
    double zoomingSpeed = CAMERA_ZOOMING_SPEED;

    void Up(double dt) {
        position.y -= dt * cameraSpeed;
        #if DEBUG_MODE
            std::cout << "Going up" << std::endl;
            std::cout << "Camera position: " << position << std::endl;
        #endif
    }
    void Down(double dt) {
        position.y += dt * cameraSpeed;
        #if DEBUG_MODE
            std::cout << "Going down" << std::endl;
            std::cout << "Camera position: " << position << std::endl;
        #endif
    }
    void Right(double dt) {
        position.x += dt * cameraSpeed;
        #if DEBUG_MODE
            std::cout << "Going right" << std::endl;
            std::cout << "Camera position: " << position << std::endl;
        #endif
    }
    void Left(double dt) {
        position.x -= dt * cameraSpeed;
        #if DEBUG_MODE
            std::cout << "Going left" << std::endl;
            std::cout << "Camera position: " << position << std::endl;
        #endif
    }

    void ZoomIn(double dt) {
        zoom += dt * zoomingSpeed;
        #if DEBUG_MODE
            std::cout << "Zooming in" << std::endl;
            std::cout << "Zoom: " << zoom << std::endl;
        #endif

    }
    void ZoomOut(double dt) {
        zoom -= dt * zoomingSpeed;
        #if DEBUG_MODE
            std::cout << "Zooming out" << std::endl;
            std::cout << "Zoom: " << zoom << std::endl;
        #endif
    }
};

#endif // CAMERA_HEADER