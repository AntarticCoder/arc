#pragma once
#include <vector>

#include "arc/arc_rigid_body.h"

namespace arc
{
    const double GRAV_CONST = -9.81f;

    class PhysicsWorld
    {
    private:
        std::vector<std::unique_ptr<RigidBody>> _bodies = {};

        double _gravity = GRAV_CONST;
    public:
        RigidBody* CreateBody(Vec3 position, double mass);
        RigidBody* CreateBody(Vec3 position, double mass, Collider* collider);

        RigidBody* AddBody(RigidBody body) {
            _bodies.push_back(std::make_unique<RigidBody>(std::move(body)));
            return _bodies.back().get();
        }

        void SetGravity(double grav) {
            _gravity = grav;
        }

        void Simulate(double timeStep);
    };
}