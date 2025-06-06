#pragma once
#include <vector>
#include <memory>

#include "arc/arc_rigid_body.h"
#include "arc/arc_object.h"

namespace arc
{
    const double GRAV_CONST = -9.81f;

    class PhysicsWorld
    {
    private:
        std::vector<std::unique_ptr<Object>> _objects= {};

        double _gravity = GRAV_CONST;
    public:
        Object* AddObject(Object obj) {
            _objects.push_back(std::make_unique<Object>(std::move(obj)));
            return _objects.back().get();
        }

        void SetGravity(double grav) {
            _gravity = grav;
        }

        void Simulate(double timeStep);
    };
}