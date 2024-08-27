#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <cmath>
#include <random>
#include <iostream>


 struct Vec3D {
    
    public:
        float x;
        float y;
        float z;

        Vec3D(float x_val, float y_val, float z_val) : x(x_val), y(y_val), z(z_val) {}

        float magnitude() const {
            return std::sqrt(x * x + y * y + z * z);
        }

        Vec3D normalize() const {
            float mag = magnitude();
            return Vec3D(x / mag, y / mag, z / mag);
        }

        float dot(const Vec3D& other) const {
            return x * other.x + y * other.y + z * other.z;
        }

        float distance(const Vec3D& other) const {
            return std::sqrt(std::pow(x - other.x, 2) + std::pow(y - other.y, 2) + std::pow(z - other.z, 2));
        }

        Vec3D cross(const Vec3D& other) const {
            return Vec3D(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
        }

        static Vec3D lerp(const Vec3D& a, const Vec3D& b, float t) {
            return a + (b - a) * t;
        }

        static Vec3D generateRandomVector(float min = 0.0f, float max = 1.0f) {
            static std::random_device rd;
            static std::mt19937 gen(rd());
            std::uniform_real_distribution<float> dist(min, max);

            return Vec3D(dist(gen), dist(gen), dist(gen));
        }

        Vec3D operator+(const Vec3D& other) const {
            return Vec3D(x + other.x, y + other.y, z + other.z);
        }

        Vec3D operator*(float scalar) const {
            return Vec3D(x * scalar, y * scalar, z * scalar);
        }

        Vec3D operator/(float scalar) const {
            return Vec3D(x / scalar, y / scalar, z / scalar);
        }

        Vec3D operator-(const Vec3D& other) const {
            return Vec3D(x - other.x, y - other.y, z - other.z);
        }

        Vec3D operator-() const {
            return Vec3D(-x, -y, -z);
        }

        Vec3D& operator+=(const Vec3D& other) {
            x += other.x;
            y += other.y;
            z += other.z;
            return *this;
        }

 };



#endif