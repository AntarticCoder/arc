#pragma once
#include "arc/math/arc_vector.h"

namespace arc
{
    class Ray
    {
    public:
        Vec3 origin;
        Vec3 direction;
        double length;
    };
}