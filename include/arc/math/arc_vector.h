#pragma once
#include <string>

namespace arc
{
    class Vec2
    {
    public:
        double x, y;

        Vec2() : x(0.0f), y(0.0f) {}
        Vec2(double x) : x(x), y(x) {}
        Vec2(double x, double y) : x(x), y(y) {}
    };

    class Vec3
    {
    public:
        double x, y, z;

        Vec3() : x(0.0f), y(0.0f), z(0.0f) {}
        Vec3(double x) : x(x), y(x), z(x) {}
        Vec3(double x, double y, double z) : x(x), y(y), z(z) {}

        Vec3& operator+=(const Vec3& other) {
            x += other.x;
            y += other.y;
            z += other.z;
            return *this;
        }

        Vec3& operator*=(const double n) {
            x *= n;
            y *= n;
            z *= n;
            return *this;
        }

        Vec3& operator/=(const double n) {
            x /= n;
            y /= n;
            z /= n;
            return *this;
        }

        double GetMagnitude() {
            return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
        }
    };

    inline Vec3 operator+(const Vec3& vec1, const Vec3& vec2)
    {
        Vec3 result = Vec3(
            vec1.x + vec2.x,
            vec1.y + vec2.y,
            vec1.z + vec2.z
        );
        return result;
    }

    inline Vec3 operator-(const Vec3& vec1, const Vec3& vec2)
    {
        Vec3 result = Vec3(
            vec1.x - vec2.x,
            vec1.y - vec2.y,
            vec1.z - vec2.z
        );
        return result;
    }

    inline Vec3 operator*(const Vec3& vec1, const Vec3& vec2)
    {
        Vec3 result = Vec3(
            vec1.x * vec2.x,
            vec1.y * vec2.y,
            vec1.z * vec2.z
        );
        return result;
    }

    inline Vec3 operator*(const Vec3& vec, const double scalar) {
       return vec * Vec3(scalar);
    }
    inline Vec3 operator*(const double scalar, const Vec3& vec) {
        return vec * scalar;
    }

    inline Vec3 operator/(const Vec3& vec1, const Vec3& vec2)
    {
        Vec3 result = Vec3(
            vec1.x / vec2.x,
            vec1.y / vec2.y,
            vec1.z / vec2.z
        );
        return result;
    }
    inline Vec3 operator/(const Vec3& vec, const double scalar) {
        return vec / Vec3(scalar);
     }
     inline Vec3 operator/(const double scalar, const Vec3& vec) {
         return vec / scalar;
     }
}