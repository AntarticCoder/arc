#pragma once
#include "arc/arc_object.h"

namespace arc
{
    class Solver
    {
    public:
        static void SolveAABBtoAABB(Object* aObj, Object* bObj);
    };
}