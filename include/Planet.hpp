#ifndef PLANET_HPP
#define PLANET_HPP

#include <iostream>
#include <vector>
#include <limits>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_render.h>
#include "Vector2.hpp"
#include "rgba.hpp"
#include "const.hpp"
#include "Camera.hpp"

struct Planet {
    large_float radius;
    RGBA color;
    large_float mass;
    Vector2 position;
    Vector2 velocity = Vector2::zero();
    Vector2 acceleration = Vector2::zero();
    Vector2 netForce = Vector2::zero();

    Planet(int64_t posX, int64_t posY, large_float r, large_float _mass, RGBA col, Camera* cam);
    Planet(large_float posX, large_float posY, large_float r, large_float _mass, RGBA col, Camera* cam);

    Vector2 getGravityForce(Planet* p, Vector2 distanceVec, large_float distance);
    void CheckAndHandleCollision(Planet* p, Vector2 distanceVec, large_float distance);
    void DoPhysicsWithPlanet(Planet* p);
    void setAcceleration();
    void Move(large_float dt);
};

#endif // PLANET_HPP
