#pragma once
#include "arc/math/arc_vector.h"
#include "arc/arc_collider.h"
#include "arc/math/arc_transform.h"

namespace arc
{
    struct RigidBodyCreateInfo
    {
        double mass = 1.0f;
        bool applyGravity = true;
        bool isStatic = false;
        bool isTrigger = false;
    };

    class RigidBody
    {
    private:
        Vec3 _position = Vec3(0.0f);
        Vec3 _velocity = Vec3(0.0f);
        Vec3 _acceleration = Vec3(0.0f);
        Vec3 _force = Vec3(0.0f);

        double _mass = 1;

        bool _trigger = false;
        bool _static = false;
        bool _applyGravity = true;
    public:
        RigidBody() {}
        RigidBody(RigidBodyCreateInfo info) : 
            _position(Vec3(0.0f)), 
            _mass(info.mass),  
            _applyGravity(info.applyGravity),
            _static(info.isStatic),
            _trigger(info.isTrigger) {}

        void AddForce(const Vec3 force);

        void Integrate(Transform& transform, double timeStep);

        Vec3 GetPosition() const { return _position; }
        Vec3 GetVelocity() const { return _velocity; }
        Vec3 GetAcceleration() const { return _acceleration; }
        double GetMass() const { return _mass; }
        bool GetTrigger() const { return _trigger; }
        bool GetStatic() const { return _static; }
        bool GetGravity() const { return _applyGravity; }

        void SetPosition(const Vec3 pos) { _position = pos; }
        void SetVelocity(const Vec3 velocity) { _velocity = velocity; }
        void SetAcceleration(const Vec3 acceleration) { _acceleration = acceleration;  }
        void SetMass(double mass) { _mass = mass; }
        void SetTrigger(bool trigger) { _trigger = trigger; }
        void SetStatic(bool stat) { _static = stat; }
        void SetGravity(bool grav) { _applyGravity = grav; }
    };
}