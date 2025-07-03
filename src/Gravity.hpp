#pragma once

#include "Physics/Engine.hpp"

#include <iostream>


namespace CG {
    Physics::floatType gravitationalConstant = 0.0001f;

    class GravityGenerator : public Physics::ForceGenerator {
        public:
            void generateForces() override {
                for (auto& obj1 : m_Objects) {
                    for (auto& obj2 : m_Objects) {
                        Physics::vec2 distance_vec = obj2->position - obj1->position;
                        Physics::floatType distance = distance_vec.length();
                        if (distance <= std::numeric_limits<Physics::floatType>::epsilon()) {
                            continue;
                        }

                        obj1->addForce(
                            (obj1->getMass() * obj2->getMass() * gravitationalConstant * distance_vec.normalized())
                            / (distance * distance)
                        );
                    }
                }
            }
            GravityGenerator(std::unordered_set<std::shared_ptr<Physics::Object>>& objs) : Physics::ForceGenerator(objs) { };
        
    };
}
