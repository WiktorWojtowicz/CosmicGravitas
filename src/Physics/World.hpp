#pragma once

#include <vector>
#include <unordered_set>
#include <memory>

#include "Object.hpp"
#include "Solver.hpp"
#include "ForceGenerator.hpp"

namespace Physics {
    class World
    {
    private:
        std::unordered_set<std::shared_ptr<Object>> m_Objects;
        std::unique_ptr<Solver> m_Solver;
        std::vector<std::unique_ptr<ForceGenerator>> m_ForceGenerators;

    public:
        World(std::unique_ptr<Solver> solver) {
            solver->passObjects(m_Objects);
            m_Solver = std::move(solver);
        }
        ~World();
        
        void addForceGenerator(std::unique_ptr<ForceGenerator> gen) {
            m_ForceGenerators.emplace_back(std::move(gen));
            gen->passObjects(m_Objects);
        }

        void addObject(const std::shared_ptr<Object> obj) {
            m_Objects.emplace(obj);
        }

        void removeObject(const std::shared_ptr<Object> obj) {
            m_Objects.erase(obj);
        }

        void update(floatType dt) {
            m_Solver->solveObjects(dt);
        }
    };
}