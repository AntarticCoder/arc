#pragma once
#include "arc/arc_rigid_body.h"

namespace arc
{
    class Solver
    {
    public:
        static void SolveAABBtoAABB(RigidBody* aBody, RigidBody* bBody);
    };
}