#include "arc/arc_physics_world.h"
#include "arc/arc_collision_detection.h"

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
        if(body->GetGravity()) {
            body->AddForce(gravForce);
        }

        body->Integrate(timeStep);
    }

    for(int i = 0; i < _bodies.size(); i++)
    {
        if(_bodies[i]->GetCollider()) 
        {
            for(int j = i + 1; j < _bodies.size(); j++)
            {
                if(!_bodies[j]->GetCollider()) continue;

                if(DetectCollision(*_bodies[i] , *_bodies[j])) {
                    std::cout << "Collision Found!!!" << std::endl;
                }
            }
        }
    }

    // std::cout << _bodies[0]->GetPosition().y << std::endl;
}