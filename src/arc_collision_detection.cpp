#include "arc/arc_collision_detection.h"

bool arc::DetectAABBtoPoint(const AABB a, const Vec3 p)
{
    if(a.basePoint.x > p.x && a.endPoint.x < p.x) {
        if(a.basePoint.y > p.y && a.endPoint.y < p.y) {
            if(a.basePoint.z > p.z && a.endPoint.z < p.z) {
                return true;
            }
        }
    }

    return false;
}

bool arc::DetectAABBtoAABB(const AABB& a, const AABB& b, const Vec3 transform)
{
    Vec3 aBasePoint = a.basePoint + transform;
    Vec3 aEndPoint = a.endPoint + transform;
    Vec3 bBasePoint = b.basePoint + transform;
    Vec3 bEndPoint = b.endPoint + transform;

    return (
        aBasePoint.x <= bEndPoint.x &&
        aEndPoint.x  >= bBasePoint.x &&
        aBasePoint.y <= bEndPoint.y &&
        aEndPoint.y  >= bBasePoint.y &&
        aBasePoint.z <= bEndPoint.z &&
        aEndPoint.z  >= bBasePoint.z
    );
}

bool arc::DetectCollision(RigidBody a, RigidBody b)
{
    Collider* aCol = a.GetCollider();
    Collider* bCol = b.GetCollider();

    if(aCol->GetType() == ColliderType::AABB)
    {
        if(bCol->GetType() == ColliderType::AABB) 
        {
            return DetectAABBtoAABB(*static_cast<AABB*>(aCol) + a.GetPosition(), *static_cast<AABB*>(bCol) + b.GetPosition());
        }
    }
    return false;
}