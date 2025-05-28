#pragma once
#include "arc/math/arc_vector.h"
#include "arc/arc_collider.h"

namespace arc
{
    class AABB : public Collider
    {   
    public:
        Vec3 basePoint;
        Vec3 endPoint;

        AABB(Vec3 basePoint, Vec3 endPoint) : basePoint(basePoint), endPoint(endPoint) {}

        ColliderType GetType() const override { return ColliderType::AABB; }
    };

    inline AABB operator+(const AABB& aabb, const Vec3& vec)
    {
        return AABB(
            aabb.basePoint + vec,
            aabb.endPoint + vec
        );
    }
}