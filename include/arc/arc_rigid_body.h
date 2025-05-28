#pragma once
#include "arc/math/arc_vector.h"
#include "arc/arc_collider.h"

namespace arc
{
    class RigidBody
    {
    private:
        Vec3 _position;
        Vec3 _velocity;
        Vec3 _acceleration;
        Vec3 _force;

        Collider* _collider = nullptr;

        double _mass = 1;

        bool _enableGravity = true;
    public:
        RigidBody(Vec3 pos, double mass ) : _position(pos), _mass(mass) {}
        RigidBody(Vec3 pos, double mass, Collider* collider) : _position(pos), _mass(mass), _collider(collider) {}

        void AddForce(const Vec3 force);

        void Integrate(double timeStep);

        void AddAABB(Vec3 basePoint, Vec3 endPoint);

        Vec3 GetPosition() const { return _position; }
        Vec3 GetVelocity() const { return _velocity; }
        Vec3 GetAcceleration() const { return _acceleration; }
        double GetMass() const { return _mass; }
        bool GetGravity() { return _enableGravity; }
        Collider* GetCollider() { return _collider; }

        void SetPosition(const Vec3 pos) { _position = pos; }
        void SetVelocity(const Vec3 velocity) { _velocity = velocity; }
        void SetAcceleration(const Vec3 acceleration) { _acceleration = acceleration;  }
        void SetMass(double mass) { _mass = mass; }
        void SetGravity(bool grav) { _enableGravity = grav; }
        void SetCollider(Collider* collider) { _collider = collider; }
    };
}