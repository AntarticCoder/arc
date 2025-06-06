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

        AABB* operator+=(const Vec3& vec)
        {
            basePoint + vec,
            endPoint + vec;
            return this;
        }
    };

    inline AABB operator+(const AABB& aabb, const Vec3& vec)
    {
        return AABB(
            aabb.basePoint + vec,
            aabb.endPoint + vec
        );
    }

    static AABB* CreateAABB(Vec3 basePoint, Vec3 endPoint) {
        return new AABB(basePoint, endPoint);
    }

    static AABB* CreateAABB(double height, double width, double depth) {
        Vec3 base = Vec3(-height/2, -width/2, -depth/2);
        Vec3 end = Vec3(height/2, width/2, depth/2);
        return new AABB(base, end);
    }
}