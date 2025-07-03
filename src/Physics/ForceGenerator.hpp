#pragma once

#include <memory>
#include <unordered_set>

#include "Object.hpp"

namespace Physics {
    class ForceGenerator
    {
    protected:
        std::unordered_set<std::shared_ptr<Object>>& m_Objects;
    public:
        ForceGenerator(std::unordered_set<std::shared_ptr<Object>>& objs) : m_Objects(objs) { };
        virtual void generateForces() = 0;
    };    
}