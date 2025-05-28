#include "arc/arc_solver.h"
#include "arc/colliders/arc_aabb.h"

using namespace arc;

void Solver::SolveAABBtoAABB(RigidBody* aBody, RigidBody* bBody)
{
    AABB a = *static_cast<AABB*>(aBody->GetCollider()) + aBody->GetPosition();
    AABB b = *static_cast<AABB*>(bBody->GetCollider()) + bBody->GetPosition();

    bool xOverlap = (a.basePoint.x < b.endPoint.x && a.endPoint.x > b.basePoint.x);
    if(!xOverlap) return;

    bool yOverlap = (a.basePoint.y < b.endPoint.y && a.endPoint.y > b.basePoint.y);
    if(!yOverlap) return;

    Vec2 AintoB = Vec2(a.endPoint.x - b.basePoint.x, a.endPoint.y - b.basePoint.y); // A moving up into B
    Vec2 BintoA = Vec2(b.endPoint.x - a.basePoint.x, b.endPoint.y - a.basePoint.y); // B moving down into A

    Vec2 intersect = Vec2(std::min(AintoB.x, BintoA.x), std::min(AintoB.y, BintoA.y));

    Vec3 shiftDirection = Vec3(0.0f, 0.0f, 0.0f);
    Vec3 collisionNormal = Vec3(0.0f, 0.0f, 0.0f);
    double actualShift = 0.0f;

    bool horizontal = false;
    if(intersect.y < intersect.x)
    {
        actualShift = intersect.y;
        if(AintoB.y > BintoA.y) {
            shiftDirection += Vec3(0.0f, 1.0f, 0.0f);
            collisionNormal += Vec3(0.0f, 1.0f, 0.0f); 
        } else {
            shiftDirection += Vec3(0.0, -1.0f, 0.0f);
            collisionNormal += Vec3(0.0f, 1.0f, 0.0f); 
        }
    } else 
    {
        actualShift = intersect.x;
        if(AintoB.x > BintoA.x) {
            shiftDirection += Vec3(1.0f, 0.0f, 0.0f);
            collisionNormal += Vec3(1.0f, 0.0f, 0.0f); 
        } else {
            shiftDirection += Vec3(-1.0, 0.0f, 0.0f);
            collisionNormal += Vec3(1.0f, 0.0f, 0.0f); 
        }
    }

    Vec3 shift = (shiftDirection * actualShift);

    if(!aBody->GetStatic()) {
        aBody->SetPosition(aBody->GetPosition() + shift);
    }   

    if(!bBody->GetStatic()) {
        bBody->SetPosition(bBody->GetPosition() - shift);
    }

    double relativeVelocityDotNormal = (aBody->GetVelocity() - bBody->GetVelocity()).Dot(collisionNormal);

    double invMassA = (1.0 / aBody->GetMass());
    double invMassB = (1.0 / bBody->GetMass());

    double totalInvMass = invMassA + invMassB;
    double RESTITUTION = 0.2;

    double impulseMagnitude = -(1.0 + RESTITUTION) * relativeVelocityDotNormal / totalInvMass;

    if(!aBody->GetStatic()) {
        aBody->SetVelocity(aBody->GetVelocity() + collisionNormal * (impulseMagnitude * invMassA));
    }

    if(!bBody->GetStatic()) {
        bBody->SetVelocity(bBody->GetVelocity() - collisionNormal * (impulseMagnitude * invMassB));
    }
}