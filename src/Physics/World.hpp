#pragma once

#include <vector>
#include <unordered_set>
#include <memory>

#include "Object.hpp"
#include "Solver.hpp"

namespace Physics {
    class World
    {
    private:
        std::unordered_set<std::shared_ptr<Object>> m_Objects;
        std::unique_ptr<Solver> m_Solver;
        

    public:
        World(std::unique_ptr<Solver> solver) {
            m_Solver = std::move(solver);
        }
        ~World();
        
        void addObject(const std::shared_ptr<Object> obj) {
            m_Objects.emplace(obj);
        }

        void removeObject(const std::shared_ptr<Object> obj) {
            m_Objects.erase(obj);
        }

        void update(floatType dt) {
            for (auto obj : m_Objects) {
                m_Solver->solveObject(*obj, dt);
            }
        }
    };
}