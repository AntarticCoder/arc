#include "arc/arc_physics_world.h"

#include <iostream>
#include <iomanip>

using namespace arc;

void PhysicsWorld::Simulate(double timeStep)
{
    for(auto& body : _bodies) {
        body.SetTimeStep(timeStep);
        
        Vec3 gravForce = Vec3(0.0f, body.mass() * _gravity, 0.0f);
        body.AddForce(gravForce);

        body.Integrate();
    }

    std::cout << "\r" << std::setw(4) << std::setfill(' ') << _bodies[0].position().y << std::flush;
}