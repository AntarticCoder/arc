#include "arc/arc_body.h"

using namespace arc;

void Body::AddForce(const Vec3 force) 
{
    _force += force;
}

void Body::Integrate()
{
    _acceleration += (_force / GetMass()); 
    _velocity += (_acceleration * _timeStep);
    _position = _position + (_velocity * _timeStep) +  ((_acceleration * 0.5f) * _timeStep * _timeStep); // Xf = Xi + VoT + 0.5AT^2
    _force = Vec3(0.0f);
}