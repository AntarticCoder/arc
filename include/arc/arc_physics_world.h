#pragma once
#include <vector>

#include "arc/arc_body.h"

namespace arc
{
    class PhysicsWorld
    {
    private:
        std::vector<Body> _bodies;
    public:
        void Simulate();
    };
}