#include "arc/arc_physics_world.h"
#include "arc/arc_collision_detection.h"
#include "arc/arc_solver.h"

#include <iostream>
#include <iomanip>

using namespace arc;

RigidBody* PhysicsWorld::CreateBody(Vec3 position, double mass){
    return CreateBody(position, mass, nullptr);
}

RigidBody* PhysicsWorld::CreateBody(Vec3 position, double mass, Collider* collider)
{
    _bodies.push_back(std::make_unique<RigidBody>(position, mass, collider));
    return _bodies.back().get();
}

void PhysicsWorld::Simulate(double timeStep)
{
    for(auto& body : _bodies) 
    {   
        Vec3 gravForce = Vec3(0.0f, body->GetMass() * _gravity, 0.0f);
        if(body->GetGravity() || body->GetStatic() || body->GetTrigger()) {
            body->AddForce(gravForce);
        }

        body->Integrate(timeStep);
    }

    int count = 0;
    for(int i = 0; i < _bodies.size(); i++)
    {
        for(int j = i + 1; j < _bodies.size(); j++)
        {
            count++;
            if(!_bodies[j]->GetCollider() || !_bodies[i]->GetCollider()) continue;

            if(DetectCollision(*_bodies[i] , *_bodies[j])) 
            {
                if(!_bodies[i]->GetTrigger() && !_bodies[j]->GetTrigger())
                {
                    Solver::SolveAABBtoAABB(_bodies[i].get(), _bodies[j].get());
                    std::cout << "Collision Found!!!" << std::endl;
                } else
                {
                    _bodies[i]->GetCollider()->TriggerCallback();
                    _bodies[j]->GetCollider()->TriggerCallback();
                }
            }
        }
    }
}