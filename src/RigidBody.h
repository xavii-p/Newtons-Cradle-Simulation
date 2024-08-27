#pragma once
#include "Vec3D.h"
#include <memory>

class RigidBody {
public:
    RigidBody(float mass, const Vec3D& pos, const Vec3D& vel);
    RigidBody(float mass);
    virtual ~RigidBody() = default;
    RigidBody(const RigidBody& other);
    RigidBody& operator=(const RigidBody& other);
    RigidBody(RigidBody&& other) noexcept;
    RigidBody& operator=(RigidBody&& other) noexcept;

    virtual void update(float dt);
    void applyForce(const Vec3D& force);
    
    const Vec3D& getPosition() const { return *Position; }
    const Vec3D& getVelocity() const { return *Velocity; }
    const Vec3D& getAcceleration() const { return *Acceleration; }
    Vec3D generateRandomVector(float min, float max);
    void updatePendulum(float dt, float length, float gravity);

protected:
    float Mass;
    std::unique_ptr<Vec3D> Position;
    std::unique_ptr<Vec3D> Velocity;
    std::unique_ptr<Vec3D> Acceleration;
};