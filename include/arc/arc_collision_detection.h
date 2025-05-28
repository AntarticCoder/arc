#pragma once
#include "arc/arc_rigid_body.h"
#include "arc/colliders/arc_aabb.h"
#include "arc/colliders/arc_ray.h"

namespace arc
{
    bool DetectAABBtoPoint(const AABB a, const Vec3 p);
    bool DetectAABBtoAABB(const AABB& a, const AABB& b, const Vec3 transform = Vec3(0.0));

    bool DetectCollision(RigidBody a, RigidBody b);
}