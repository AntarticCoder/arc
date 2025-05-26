#pragma once
#include <string>

namespace arc
{
    class Vec3
    {
    public:
        double x, y, z;

        Vec3() : x(0.0f), y(0.0f), z(0.0f) {}
        Vec3(double x) : x(x), y(x), z(x) {}
        Vec3(double x, double y, double z) : x(x), y(y), z(z) {}

        Vec3 operator+(const Vec3 other) {
            Vec3 vec(
                x + other.x,
                y + other.y, 
                z + other.z
            );
            return vec;
        }

        Vec3& operator+=(const Vec3& other) {
            x += other.x;
            y += other.y;
            z += other.z;
            return *this;
        }

        Vec3& operator*(const double n) {
            x /= n;
            y /= n;
            z /= n;
            return *this;
        }

        Vec3& operator/(const double n) {
            x /= n;
            y /= n;
            z /= n;
            return *this;
        }
    };
}