#pragma once
#include "RigidBody.h"

class Ball : public RigidBody {
    public:
        Ball(float mass, float radius, const Vec3D& pos, const Vec3D& vel);
        Ball(float mass, float radius);

        float getRadius() const;
        Vec3D getPosition() const;
        Vec3D getVelocity() const;
        float getMass() const;

        void setPosition(const Vec3D& pos);
        void setVelocity(const Vec3D& vel);
        void setRadius(float radius);

        bool isColliding(const Ball& other) const;
        void handleCollision(Ball& other);
        void updatePendulum(float dt, float length, float gravity);

        static Ball lerp(const Ball& a, const Ball& b, float t);

    private:
        float radius;
};