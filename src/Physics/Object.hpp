#pragma once

#include <SFML/System/Vector2.hpp>

#include "Vector.hpp"

/*
TODO: Make accelerated version & other solvers
*/

namespace Physics {
    using vec2 = sf::Vector2<floatType>;

    class Object {
    private:
        floatType m_Mass;
        floatType m_MassInverse;
    public:
        vec2 position = vec2(0, 0);
        vec2 velocity = vec2(0, 0);
        vec2 acceleration = vec2(0, 0);
        vec2 forces = vec2(0, 0);

        Object();
        Object(floatType mass, vec2 pos, vec2 vel) : position(pos), velocity(vel) {
            setMass(mass);
        }

        floatType& getMass() {
            return m_Mass;
        }

        floatType& getMassInverse() {
            return m_MassInverse;
        }

        void setMass(floatType value) {
            m_Mass = value;
            m_MassInverse = 1 / m_Mass;
        }

        void addForce(vec2 force) {
            forces += force;
        }


    };
}