#include "Camera.hpp"

void Camera::Up(large_float dt) {
    position.y -= dt * cameraSpeed / zoom;
    #if DEBUG_MODE
        std::cout << "Going up" << std::endl;
        std::cout << "Camera position: " << position << std::endl;
    #endif
}

void Camera::Down(large_float dt) {
    position.y += dt * cameraSpeed / zoom;
    #if DEBUG_MODE
        std::cout << "Going down" << std::endl;
        std::cout << "Camera position: " << position << std::endl;
    #endif
}

void Camera::Right(large_float dt) {
    position.x += dt * cameraSpeed / zoom;
    #if DEBUG_MODE
        std::cout << "Going right" << std::endl;
        std::cout << "Camera position: " << position << std::endl;
    #endif
}

void Camera::Left(large_float dt) {
    position.x -= dt * cameraSpeed / zoom;
    #if DEBUG_MODE
        std::cout << "Going left" << std::endl;
        std::cout << "Camera position: " << position << std::endl;
    #endif
}

void Camera::ZoomOut(large_float dt) {
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

void Camera::ZoomIn(large_float dt) {
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
