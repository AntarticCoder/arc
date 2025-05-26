#include <chrono>
#include <thread>

#include "arc/arc_physics_world.h"

int main()
{
    arc::PhysicsWorld world;
    arc::Body body = arc::Body(arc::Vec3(), 2.0);
    world.AddBody(body);

    const double timeStep = 1.0 / 60.0; 
    const auto timeStepDuration = std::chrono::duration<double>(timeStep);

    auto previous = std::chrono::steady_clock::now();
    double accumulator = 0.0;

    while(true) 
    {
        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<double> frameTime = now - previous;
        previous = now;

        accumulator += frameTime.count();

        while(accumulator >= timeStep) 
        {
            world.Simulate(timeStep);
            accumulator -= timeStep;
        }
    }
    return 0;
}