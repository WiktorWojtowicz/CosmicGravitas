#pragma once

#include <SFML/System/Vector2.hpp>

#include "Vector.hpp"

namespace Physics {
    using vec2 = sf::Vector2<floatType>;

    struct Object
    {
        vec2 position;
        vec2 velocity;
        vec2 acceleration;
        floatType mass;

        void addForce(vec2 force) {
            acceleration += force / mass;
        }
    };
}