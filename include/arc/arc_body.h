#pragma once
#include "arc/math/arc_vector.h"

namespace arc
{
    class Body
    {
    private:
        Vec3 _position;
        Vec3 _velocity;
        Vec3 _acceleration;
        Vec3 _force;

        double _mass = 1;
        double _timeStep = 1.0f;
    public:
        Body(Vec3 pos, double mass) : _position(pos), _mass(mass) {}

        void AddForce(const Vec3 force);
        void SetTimeStep(double timeStep) { _timeStep = timeStep; }

        void Integrate();

        Vec3 position() const { return _position; }
        Vec3 velocity() const { return _velocity; }
        Vec3 acceleration() const { return _acceleration; }
        double mass() const { return _mass; }
    };
}