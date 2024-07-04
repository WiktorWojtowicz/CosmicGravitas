#ifndef CAMERA_HEADER
#define CAMERA_HEADER

#include <iostream>
#include <cmath>
#include "const.hpp"


struct Camera
{
    const double cameraSpeed = CAMERA_SPEED;
    Vector2 position = Vector2::zero();
    double zoom = INITIAL_CAMERA_ZOOM;
    double zoomingSpeed = CAMERA_ZOOMING_SPEED;

    void Up(double dt) {
        position.y -= dt * cameraSpeed / zoom;
        #if DEBUG_MODE
            std::cout << "Going up" << std::endl;
            std::cout << "Camera position: " << position << std::endl;
        #endif
    }
    void Down(double dt) {
        position.y += dt * cameraSpeed / zoom;
        #if DEBUG_MODE
            std::cout << "Going down" << std::endl;
            std::cout << "Camera position: " << position << std::endl;
        #endif
    }
    void Right(double dt) {
        position.x += dt * cameraSpeed / zoom;
        #if DEBUG_MODE
            std::cout << "Going right" << std::endl;
            std::cout << "Camera position: " << position << std::endl;
        #endif
    }
    void Left(double dt) {
        position.x -= dt * cameraSpeed / zoom;
        #if DEBUG_MODE
            std::cout << "Going left" << std::endl;
            std::cout << "Camera position: " << position << std::endl;
        #endif
    }

    void ZoomIn(double dt) {
        double prevZoom = zoom;

        if (zoom > 1.0f) {
            zoom += dt * zoomingSpeed / zoom;
        } else {
            zoom += dt * zoomingSpeed * zoom;
        }

        zoom = std::min(MAX_CAMERA_ZOOM, zoom);

        double deltaZoom = zoom - prevZoom;

        Vector2 zoomCenter(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
        Vector2 cameraMove = (position - zoomCenter) * (deltaZoom / zoom);

        position -= cameraMove;

        #if DEBUG_MODE
            std::cout << "Zooming in" << std::endl;
            std::cout << "Zoom: " << zoom << std::endl;
        #endif

    }
    void ZoomOut(double dt) {
        double prevZoom = zoom;

        if (zoom > 1.0f) {
            zoom -= dt * zoomingSpeed / zoom;
        } else {
            zoom -= dt * zoomingSpeed * zoom;
        }
        
        zoom = std::max(MIN_CAMERA_ZOOM, zoom);

        double deltaZoom = zoom - prevZoom;

        Vector2 zoomCenter(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
        Vector2 cameraMove = (position - zoomCenter) * (deltaZoom / zoom);

        position -= cameraMove;

        #if DEBUG_MODE
            std::cout << "Zooming out" << std::endl;
            std::cout << "Zoom: " << zoom << std::endl;
        #endif
    }
};

#endif // CAMERA_HEADER