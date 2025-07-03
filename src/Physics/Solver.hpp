#pragma once

#include <unordered_set>
#include <memory>

#include "Object.hpp"


namespace Physics {
    class Solver
    {
    protected:
        std::unordered_set<std::shared_ptr<Object>>& m_Objects;
    public:
        virtual void solveObjects(floatType dt) = 0;
        void passObjects(std::unordered_set<std::shared_ptr<Object>>& obj) {
            m_Objects = obj;
        }
        Solver(std::unordered_set<std::shared_ptr<Object>>& objs) : m_Objects(objs) { }
    };    
}