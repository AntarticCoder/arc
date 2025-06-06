#include "arc/arc_physics_world.h"
#include "arc/arc_collision_detection.h"
#include "arc/arc_solver.h"

#include <iostream>
#include <iomanip>

using namespace arc;

void PhysicsWorld::Simulate(double timeStep)
{
    for(auto &object : _objects)
    {
        RigidBody& rigidBody = object->rigidBody;
        Transform& transform = object->transform;

        Vec3 gravForce = Vec3(0.0f, rigidBody.GetMass() * _gravity, 0.0f);

        if(rigidBody.GetGravity() && !rigidBody.GetStatic() && !rigidBody.GetTrigger()) {
            rigidBody.AddForce(gravForce);
        }

        rigidBody.Integrate(transform, timeStep);
    }

    int count = 0;
    for(int i = 0; i < _objects.size(); i++)
    {
        for(int j = i + 1; j < _objects.size(); j++)
        {
            count++;

            if(!_objects[i]->collider || !_objects[j]->collider)
                continue;

            if(DetectCollision(*_objects[i], *_objects[j]))
            {
                if(!_objects[i]->rigidBody.GetTrigger() && !_objects[j]->rigidBody.GetTrigger())
                {
                    Solver::SolveAABBtoAABB(_objects[i].get(), _objects[j].get());
                    std::cout << "Collision Found!!!" << std::endl;
                }
                else
                {
                    _objects[i]->collider->TriggerCallback();
                    _objects[j]->collider->TriggerCallback();
                }
            }
        }
    }
}