#pragma once
#include <vector>

#include "arc/arc_body.h"

namespace arc
{
    const double GRAV_CONST = -9.81f;

    class PhysicsWorld
    {
    private:
        std::vector<Body> _bodies = {};

        double _gravity = GRAV_CONST;
    public:
        Body* AddBody(Body body) {
            _bodies.push_back(body);
            return &_bodies.back();
        }

        void SetGravity(double grav) {
            _gravity = grav;
        }

        void Simulate(double timeStep);
    };
}