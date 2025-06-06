#include "arc/arc_collision_detection.h"

bool arc::DetectAABBtoPoint(const AABB a, const Vec3 p)
{
    return (
        a.basePoint.x > p.x &&
        a.endPoint.x  < p.x &&
        a.basePoint.y > p.y &&
        a.endPoint.y  < p.y && 
        a.basePoint.z > p.z && 
        a.endPoint.z  < p.z
    );
}

bool arc::DetectAABBtoAABB(const AABB& a, const AABB& b)
{
    return (
        a.basePoint.x <= b.endPoint.x &&
        a.endPoint.x  >= b.basePoint.x &&
        a.basePoint.y <= b.endPoint.y &&
        a.endPoint.y  >= b.basePoint.y &&
        a.basePoint.z <= b.endPoint.z &&
        a.endPoint.z  >= b.basePoint.z
    );
}

bool arc::DetectCollision(Object a, Object b)
{
    Collider* aCol = a.collider;
    Collider* bCol = b.collider;

    if(aCol->GetType() == ColliderType::AABB)
    {
        if(bCol->GetType() == ColliderType::AABB) 
        {
            return DetectAABBtoAABB(*static_cast<AABB*>(aCol) + a.transform.position, *static_cast<AABB*>(bCol) + b.transform.position);
        }
    }
    return false;
}