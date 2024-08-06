#ifndef CAMERA_HEADER
#define CAMERA_HEADER

#include <iostream>
#include <cmath>
#include "const.hpp"
#include "Vector2.hpp"


struct Camera {
    large_float cameraSpeed = CAMERA_SPEED;
    Vector2 position = Vector2::zero();
    large_float zoom = INITIAL_CAMERA_ZOOM;
    large_float zoomingSpeed = CAMERA_ZOOMING_SPEED;

    void Up(large_float dt);
    void Down(large_float dt);
    void Right(large_float dt);
    void Left(large_float dt);
    void ZoomOut(large_float dt);
    void ZoomIn(large_float dt);
};

#endif // CAMERA_HEADER
