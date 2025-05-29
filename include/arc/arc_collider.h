#pragma once
#include <functional>

namespace arc
{
    typedef std::function<void()> CollisionCallback;
    
    enum class ColliderType
    {
        NONE = 0,
        AABB = 1,
        SPHERE = 2
    };

    class Collider
    {
    private:
        CollisionCallback _collideCallback = DefaultCollisionCallback;
    public:
        static void DefaultCollisionCallback() {}

        void SetCallback(CollisionCallback callback) {
            _collideCallback = callback;
        }

        void TriggerCallback() {
            _collideCallback();
        }

        virtual ColliderType GetType() const = 0;
    };
};