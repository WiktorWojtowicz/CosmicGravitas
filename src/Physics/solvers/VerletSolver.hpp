#pragma once

#include "../Solver.hpp"
#include <iostream>

namespace Physics {
    namespace Solvers {
        class Verlet : public Solver {
            private:
                void solveObject(Object& obj, floatType dt) {
                    vec2 new_pos = obj.position + (obj.velocity * dt) + (obj.acceleration*dt*dt * 0.5);
                    vec2 new_acc = obj.forces * obj.getMassInverse();
                    vec2 new_vel = obj.velocity + ((obj.acceleration + new_acc)*(dt*0.5));

                    obj.position = new_pos;
                    obj.velocity = new_vel;
                    obj.acceleration = new_acc;
                }
            public:
                void solveObjects(floatType dt) override {
                    for (auto& obj : m_Objects) {
                        solveObject(*obj, dt);
                    }
                }
                Verlet(std::unordered_set<std::shared_ptr<Object>>& objs) : Solver(objs) {}
        };
    }
}
