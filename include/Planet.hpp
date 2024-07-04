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

    Planet(int64_t posX, int64_t posY, int64_t r, large_float _mass, RGBA col, Camera* cam)
        : radius(r), mass(_mass), color(col) {
        position.x = ((static_cast<large_float>(posX)) / cam->zoom) + cam->position.x;
        position.y = ((static_cast<large_float>(posY)) / cam->zoom) + cam->position.y;
    }

    Vector2 getGravityForce(Planet* p, Vector2 distanceVec, large_float distance) {
        if (distance == 0) return Vector2::zero();

        large_float forceMagnitude = GRAVITATIONAL_CONSTANT * (this->mass * p->mass) / (distance * distance);
        distanceVec.normalize();
        Vector2 force = distanceVec * forceMagnitude;
        return force;
    }

    void CheckAndHandleCollision(Planet* p, Vector2 distanceVec, large_float distance) {
        large_float overlap = (this->radius + p->radius - distance) / 2.0;

        if (overlap > std::numeric_limits<large_float>::epsilon()) {
            Vector2 overlapDir = distanceVec;
            overlapDir.normalize();

            this->position -= overlapDir * overlap * (p->mass / (this->mass + p->mass));
            p->position += overlapDir * overlap * (this->mass / (this->mass + p->mass));

            Vector2 normal = distanceVec;
            normal.normalize();
            
            Vector2 tangent = Vector2(-normal.y, normal.x);

            large_float dpTan1 = this->velocity.dot(tangent);
            large_float dpTan2 = p->velocity.dot(tangent);

            large_float dpNorm1 = this->velocity.dot(normal);
            large_float dpNorm2 = p->velocity.dot(normal);

            large_float m1 = this->mass;
            large_float m2 = p->mass;

            large_float newDpNorm1 = (dpNorm1 * (m1 - m2) + 2.0 * m2 * dpNorm2) / (m1 + m2);
            large_float newDpNorm2 = (dpNorm2 * (m2 - m1) + 2.0 * m1 * dpNorm1) / (m1 + m2);

            this->velocity = tangent * dpTan1 + normal * newDpNorm1;
            p->velocity = tangent * dpTan2 + normal * newDpNorm2;
        }
    }

    void DoPhysicsWithPlanet(Planet* p) {
        Vector2 distanceVec = p->position - this->position;
        large_float distance = distanceVec.magnitude();

        Vector2 gravityForce = getGravityForce(p, distanceVec, distance);
        netForce += gravityForce;
        p->netForce -= gravityForce;

        CheckAndHandleCollision(p, distanceVec, distance);
    }

    void setAcceleration() {
        acceleration = netForce / this->mass;
        netForce = Vector2::zero();
        #if DEBUG_MODE
        std::cout << "Acceleration: " << acceleration
                << " Velocity: " << velocity
                << " Position: " << position
                << std::endl;
        #endif
    }

    void Move(large_float dt) {
        dt *= TIME_MULTIPLIER;
        position += velocity * dt + acceleration * dt * dt * 0.5;
        velocity += acceleration * dt;
        acceleration = Vector2::zero();
    }
};

#endif // PLANET_HPP
