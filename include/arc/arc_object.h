#pragma once
#include "arc/math/arc_transform.h"
#include "arc/arc_collider.h"
#include "arc/arc_rigid_body.h"

namespace arc
{
    struct Object
    {
        Transform transform;
        RigidBody rigidBody;
        Collider* collider = nullptr;
    };
}