#include "RigidBody.h"
#include "Vec3D.h"
#include <cmath>
#include <iostream>
#include <memory>
#include <random>



// constructor to specify position and velocity of a body
RigidBody::RigidBody(float m, const Vec3D& pos, const Vec3D& vel)
    : Mass(m), Position(std::make_unique<Vec3D>(pos)), Velocity(std::make_unique<Vec3D>(vel)), Acceleration(std::make_unique<Vec3D>(0.0f, 0.0f, 0.0f)), angularVelocity(0.0f, 0.0f, 0.0f), torque(0.0f, 0.0f, 0.0f), momentOfInertia(0.0f) {}

RigidBody::RigidBody(const RigidBody& other)
    : Mass(other.Mass), Position(std::make_unique<Vec3D>(*other.Position)), Velocity(std::make_unique<Vec3D>(*other.Velocity)), Acceleration(std::make_unique<Vec3D>(*other.Acceleration)), angularVelocity(other.angularVelocity), torque(other.torque), momentOfInertia(other.momentOfInertia) {}

RigidBody& RigidBody::operator=(const RigidBody& other) {
    if (this != &other) {
        Mass = other.Mass;
        *Position = *other.Position;
        *Velocity = *other.Velocity;
        *Acceleration = *other.Acceleration;
        angularVelocity = other.angularVelocity;
        torque = other.torque;
        momentOfInertia = other.momentOfInertia;
    }
    return *this;
}

RigidBody::RigidBody(RigidBody&& other) noexcept
    : Mass(other.Mass), Position(std::move(other.Position)), Velocity(std::move(other.Velocity)), Acceleration(std::move(other.Acceleration)), angularVelocity(other.angularVelocity), torque(other.torque), momentOfInertia(other.momentOfInertia) {}

RigidBody& RigidBody::operator=(RigidBody&& other) noexcept {
    if (this != &other) {
        Mass = other.Mass;
        Position = std::move(other.Position);
        Velocity = std::move(other.Velocity);
        Acceleration = std::move(other.Acceleration);
        angularVelocity = other.angularVelocity;
        torque = other.torque;
        momentOfInertia = other.momentOfInertia;
    }
    return *this;
}

// constructor to create a randomly placed particle
RigidBody::RigidBody(float m)
    : Mass(m),
      Position(std::make_unique<Vec3D>(Vec3D(0, 0, 0).generateRandomVector(-10.0f, 10.0f))),
      Velocity(std::make_unique<Vec3D>(0.0f, 0.0f, 0.0f)),
      Acceleration(std::make_unique<Vec3D>(0.0f, 0.0f, 0.0f)),
      angularVelocity(0.0f, 0.0f, 0.0f),
      torque(0.0f, 0.0f, 0.0f),
      momentOfInertia(0.0f) {}

void RigidBody::applyForce(const Vec3D& force) {
    *Acceleration += force / Mass;
}



void RigidBody::updatePendulum(float dt, float length, float gravity) {
    // Corrected gravity vector
    const Vec3D g(0.0f, -gravity, 0.0f);
    momentOfInertia = Mass * length * length; // For a point mass at the end of a massless rod
    
    // Calculate current state
    float theta = std::atan2(Position->x, -Position->y);
    Vec3D pivot(0.0f, 0.0f, 0.0f);
    Vec3D r = *Position - pivot;
    
    // Calculate forces
    Vec3D gravityForce = g * Mass; // Corrected gravity force calculation
    Vec3D tensionDirection = -r.normalize();
    
    // Calculate tension force magnitude (centripetal force + gravity component)
    float omega = angularVelocity.magnitude();
    float tensionMagnitude = Mass * (length * omega * omega + gravity * std::cos(theta));
    Vec3D tensionForce = tensionDirection * tensionMagnitude;
    
    // Net force
    Vec3D netForce = gravityForce + tensionForce;
    
    // Calculate torque
    torque = r.cross(netForce);
    
    // Update angular acceleration
    Vec3D angularAcceleration = torque / momentOfInertia;
    
    // Update angular velocity using RK4
    Vec3D k1 = angularAcceleration * dt;
    Vec3D k2 = (angularAcceleration + k1 * 0.5f) * dt;
    Vec3D k3 = (angularAcceleration + k2 * 0.5f) * dt;
    Vec3D k4 = (angularAcceleration + k3) * dt;
    
    angularVelocity += (k1 + k2 * 2.0f + k3 * 2.0f + k4) * (1.0f/6.0f);
    
    // Apply damping to angular velocity (optional, for more realistic behavior)
    const float damping = 0.999f;
    angularVelocity *= damping;  // Scale the vector by the damping factor
    
    // Update position
    float newTheta = theta + angularVelocity.magnitude() * dt;
    Position->x = length * std::sin(newTheta);
    Position->y = -length * std::cos(newTheta);
    
    // Update linear velocity based on angular motion
    *Velocity = angularVelocity.cross(r);
    
    // Update acceleration for visualization or other purposes
    *Acceleration = netForce / Mass;
}


// Add this method to calculate derivatives
RigidBody::State RigidBody::calculateDerivatives(const Vec3D& pos, const Vec3D& vel) const {
    RigidBody::State derivatives;
    derivatives.Position = vel;  // dx/dt = v
    derivatives.Velocity = *Acceleration;  // dv/dt = a
    return derivatives;
}

void RigidBody::updateRK4(float dt) {
    // Store initial state
    Vec3D initialPos = *Position;
    Vec3D initialVel = *Velocity;
    
    // Calculate k1
    State k1 = calculateDerivatives(initialPos, initialVel);
    
    // Calculate k2
    Vec3D pos2 = initialPos + k1.Velocity * (dt/2.0f);
    Vec3D vel2 = initialVel + k1.Velocity * (dt/2.0f); // Use k1.Velocity as acceleration
    State k2 = calculateDerivatives(pos2, vel2);
    
    // Calculate k3
    Vec3D pos3 = initialPos + k2.Velocity * (dt/2.0f);
    Vec3D vel3 = initialVel + k2.Velocity * (dt/2.0f); // Use k2.Velocity as acceleration
    State k3 = calculateDerivatives(pos3, vel3);
    
    // Calculate k4
    Vec3D pos4 = initialPos + k3.Velocity * dt;
    Vec3D vel4 = initialVel + k3.Velocity * dt; // Use k3.Velocity as acceleration
    State k4 = calculateDerivatives(pos4, vel4);
    
    // Update position and velocity using weighted average
    *Position = initialPos + (dt/6.0f) * (k1.Position + 2.0f*k2.Position + 2.0f*k3.Position + k4.Position);
    *Velocity = initialVel + (dt/6.0f) * (k1.Velocity + 2.0f*k2.Velocity + 2.0f*k3.Velocity + k4.Velocity);
}

