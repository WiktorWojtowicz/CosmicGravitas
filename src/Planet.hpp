#pragma once

#include "Physics/Engine.hpp"
#include <SFML/Graphics/Texture.hpp>

namespace CG {
    class Planet : public Physics::Object {
        public:
            Physics::floatType radius;
            sf::Texture texture;
    };
}