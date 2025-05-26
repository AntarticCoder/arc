#include "arc/arc_body.h"

using namespace arc;

void Body::AddForce(const Vec3 force) 
{
    _force += force;
}

void Body::Integrate()
{
    // _acceleration.x += (_force.x / mass());
    // _acceleration.y += (_force.y / mass());
    // _acceleration.z += (_force.z / mass());

    _acceleration += (_force / mass()); 

    // Calculate change in velocity
    // _velocity.x += (_acceleration.x * _timeStep);
    // _velocity.y += (_acceleration.y * _timeStep);
    // _velocity.z += (_acceleration.z * _timeStep);

    _velocity += (_acceleration * _timeStep);

    // Calculate change in position
    // _position.x = _position.x + (_velocity.x * _timeStep) + (0.5f * _acceleration.x *_timeStep * _timeStep); // Xf = Xi + VoT + 0.5AT^2
    // _position.y = _position.y + (_velocity.y * _timeStep) + (0.5f * _acceleration.y *_timeStep * _timeStep);
    // _position.z = _position.z + (_velocity.z * _timeStep) + (0.5f * _acceleration.z *_timeStep * _timeStep);

    _position = _position + (_velocity * _timeStep) +  ((_acceleration * 0.5f) * _timeStep * _timeStep); // Xf = Xi + VoT + 0.5AT^2

    _force = Vec3(0.0f);
}