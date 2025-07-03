#pragma once

#include <vector>
#include <unordered_set>
#include <memory>

#include "Object.hpp"
#include "Solver.hpp"
#include "ForceGenerator.hpp"

namespace Physics {
    
    template <typename T, typename = typename std::enable_if<std::is_base_of<Solver, T>::value>::type>
    class World
    {
    private:
        std::unordered_set<std::shared_ptr<Object>> m_Objects;
        T m_Solver;
        std::vector<std::unique_ptr<ForceGenerator>> m_ForceGenerators;

    public:
        World() : m_Solver(m_Objects) { }

        template <typename A, typename = typename std::enable_if<std::is_base_of<ForceGenerator, A>::value>::type>
        void addForceGenerator() {
            m_ForceGenerators.emplace_back(std::move(std::make_unique<A>(m_Objects)));
        }

        void addObject(const std::shared_ptr<Object> obj) {
            m_Objects.emplace(obj);
        }

        void removeObject(const std::shared_ptr<Object> obj) {
            m_Objects.erase(obj);
        }

        void update(floatType dt) {
            for (auto& generator : m_ForceGenerators) {
                generator->generateForces();
            }
            m_Solver.solveObjects(dt);
        }

        const std::unordered_set<std::shared_ptr<Object>> getObjects() {
            return m_Objects;
        }
    };
}