#include "arc/arc_rigid_body.h"
#include "arc/colliders/arc_aabb.h"

using namespace arc;

void RigidBody::AddForce(const Vec3 force) 
{
    _force += force;
}

void RigidBody::Integrate(Transform& transform, double timeStep)
{
    _position = transform.position;

    _acceleration = (_force / GetMass()); 
    _velocity += (_acceleration * timeStep);

    if(GetVelocity().y < -50.0f) {
        SetVelocity(Vec3(GetVelocity().x, -50.0f, GetVelocity().z));
    }

    _position = _position + (_velocity * timeStep) +  ((_acceleration * 0.5f) * timeStep * timeStep); // Xf = Xi + VoT + 0.5AT^2
    _force = Vec3(0.0f);

    transform.position = _position;
}