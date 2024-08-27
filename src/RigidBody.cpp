#include "RigidBody.h"
#include "Vec3D.h"
#include <cmath>
#include <iostream>
#include <memory>
#include <random>

// constructor to specify position and velocity of a body
RigidBody::RigidBody(float m, const Vec3D& pos, const Vec3D& vel)
    : Mass(m), Position(std::make_unique<Vec3D>(pos)), Velocity(std::make_unique<Vec3D>(vel)), Acceleration(std::make_unique<Vec3D>(0.0f, 0.0f, 0.0f)) {}

RigidBody::RigidBody(const RigidBody& other)
    : Mass(other.Mass), Position(std::make_unique<Vec3D>(*other.Position)), Velocity(std::make_unique<Vec3D>(*other.Velocity)), Acceleration(std::make_unique<Vec3D>(*other.Acceleration)) {}

RigidBody& RigidBody::operator=(const RigidBody& other) {
    if (this != &other) {
        Mass = other.Mass;
        *Position = *other.Position;
        *Velocity = *other.Velocity;
        *Acceleration = *other.Acceleration;
    }
    return *this;
}

RigidBody::RigidBody(RigidBody&& other) noexcept
    : Mass(other.Mass), Position(std::move(other.Position)), Velocity(std::move(other.Velocity)), Acceleration(std::move(other.Acceleration)) {}

RigidBody& RigidBody::operator=(RigidBody&& other) noexcept {
    if (this != &other) {
        Mass = other.Mass;
        Position = std::move(other.Position);
        Velocity = std::move(other.Velocity);
        Acceleration = std::move(other.Acceleration);
    }
    return *this;
}

// constructor to create a randomly placed particle
RigidBody::RigidBody(float m) {
    Mass = m;
    // generate a random position vector
    Position = std::make_unique<Vec3D>(Vec3D(0, 0, 0).generateRandomVector(-10.0f, 10.0f));

    Velocity = std::make_unique<Vec3D>(0.0f, 0.0f, 0.0f);
    Acceleration = std::make_unique<Vec3D>(0.0f, 0.0f, 0.0f);
}

void RigidBody::applyForce(const Vec3D& force) {
    // simplified F = ma
    Vec3D acceleration = force / Mass;
    *Velocity += acceleration;
}

//update position of rigid body
void RigidBody::update(float dt) {
    // simplified x = x_o + vt
    *Position += *Velocity * dt;
}


// Add the new method here
void RigidBody::updatePendulum(float dt, float length, float gravity) {
    // Pendulum physics calculations
    float theta = std::atan2(Position->x, -Position->y);  // Angle from vertical
    float omega = Velocity->x / length;  // Angular velocity
    
    // Calculate angular acceleration
    float alpha = -gravity / length * std::sin(theta);
    
    // Update angular velocity
    omega += alpha * dt;
    
    // Update angle
    theta += omega * dt;
    
    // Update position
    Position->x = length * std::sin(theta);
    Position->y = -length * std::cos(theta);
    
    // Update velocity
    Velocity->x = length * omega * std::cos(theta);
    Velocity->y = length * omega * std::sin(theta);
}

