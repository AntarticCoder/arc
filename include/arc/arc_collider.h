#pragma once

namespace arc
{
    enum class ColliderType
    {
        NONE = 0,
        AABB = 1,
        SPHERE = 2
    };

    class Collider
    {
    public:
        virtual ColliderType GetType() const = 0;
    };
};