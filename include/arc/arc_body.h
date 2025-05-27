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

        Vec3 GetPosition() const { return _position; }
        Vec3 GetVelocity() const { return _velocity; }
        Vec3 GetAcceleration() const { return _acceleration; }
        double GetMass() const { return _mass; }

        void SetPosition(const Vec3 pos) { _position = pos; }
        void SetVelocity(const Vec3 velocity) { _velocity = velocity; }
        void SetAcceleration(const Vec3 acceleration) { _acceleration = acceleration;  }
    };
}