#pragma once
#include "Vec3D.h"
#include <memory>

class RigidBody {
private:
    struct State {
        Vec3D Position;
        Vec3D Velocity;
    };

    State calculateDerivatives(const Vec3D& pos, const Vec3D& vel) const;
    State calculateRK4(const State& initialState, float dt);
    Vec3D angularVelocity;
    Vec3D torque;
    float momentOfInertia;

public:
    RigidBody(float mass, const Vec3D& pos, const Vec3D& vel);
    RigidBody(float mass);
    virtual ~RigidBody() = default;
    RigidBody(const RigidBody& other);
    RigidBody& operator=(const RigidBody& other);
    RigidBody(RigidBody&& other) noexcept;
    RigidBody& operator=(RigidBody&& other) noexcept;

    void applyForce(const Vec3D& force);
    
    Vec3D getPosition() const { return *Position; }
    Vec3D getVelocity() const { return *Velocity; }
    Vec3D getAcceleration() const { return *Acceleration; }
    float getMass() const { return Mass; }
    
    void setPosition(const Vec3D& pos) { *Position = pos; }
    void setVelocity(const Vec3D& vel) { *Velocity = vel; }
    void setAcceleration(const Vec3D& acc) { *Acceleration = acc; }
    Vec3D generateRandomVector(float min, float max);
    void updatePendulum(float dt, float length, float gravity);
    void updateRK4(float dt);
    const Vec3D& getAngularVelocity() const { return angularVelocity; }
    const Vec3D& getTorque() const { return torque; }
    float getMomentOfInertia() const { return momentOfInertia; }

protected:
    float Mass;
    std::unique_ptr<Vec3D> Position;
    std::unique_ptr<Vec3D> Velocity;
    std::unique_ptr<Vec3D> Acceleration;
};