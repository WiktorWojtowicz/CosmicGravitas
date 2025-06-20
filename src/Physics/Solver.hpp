#pragma once
#include <Object.hpp>

namespace Physics {
    class Solver
    {
    private:
    public:
        virtual void solveObject(Object& obj, floatType dt) = 0;
        Solver();
        ~Solver();
    };    
}