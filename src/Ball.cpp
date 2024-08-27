#include "Ball.h"
#include <cmath>

Ball::Ball(float mass, float radius, const Vec3D& pos, const Vec3D& vel)
    : RigidBody(mass, pos, vel), radius(radius) {}

Ball::Ball(float mass, float radius)
    : RigidBody(mass), radius(radius) {}

float Ball::getRadius() const {
    return this->radius;
}

Vec3D Ball::getPosition() const {
    return *Position;
}

Vec3D Ball::getVelocity() const {
    return *Velocity;
}

float Ball::getMass() const {
    return this->Mass;
}

void Ball::setPosition(const Vec3D& pos) {
    *Position = pos;
}

void Ball::setVelocity(const Vec3D& vel) {
    *Velocity = vel;
}

void Ball::setRadius(float radius) {
    this->radius = radius;
}

bool Ball::isColliding(const Ball& other) const {
    return (getPosition() - other.getPosition()).magnitude() <= (radius + other.radius);
}

void Ball::handleCollision(Ball& other) {
    Vec3D normal = (getPosition() - other.getPosition()).normalize();
    Vec3D relativeVelocity = getVelocity() - other.getVelocity();
    
    float velocityAlongNormal = relativeVelocity.dot(normal);
    
    // Do not resolve if velocities are separating
    if (velocityAlongNormal > 0)
        return;

    // Calculate restitution (coefficient of restitution)
    float e = 0.9f; // Slightly less than 1 for a small energy loss

    // Calculate impulse scalar
    float j = -(1 + e) * velocityAlongNormal;
    j /= 1 / getMass() + 1 / other.getMass();

    // Apply impulse
    Vec3D impulse = normal * j;
    setVelocity(getVelocity() + impulse / getMass());
    other.setVelocity(other.getVelocity() - impulse / other.getMass());

    // Separate the balls to prevent sticking
    float overlap = radius + other.radius - (getPosition() - other.getPosition()).magnitude();
    Vec3D separationVector = normal * overlap * 0.5f;
    setPosition(getPosition() + separationVector);
    other.setPosition(other.getPosition() - separationVector);
}

void Ball::updatePendulum(float dt, float length, float gravity) {
    // Calculate the angle from the vertical
    float angle = std::atan2(Position->x, -Position->y);
    
    // Calculate angular acceleration
    float angularAcceleration = -gravity / length * std::sin(angle);
    
    // Update angular velocity
    float angularVelocity = Velocity->x / length; // Approximate angular velocity
    angularVelocity += angularAcceleration * dt;
    
    // Update angle
    angle += angularVelocity * dt;
    
    // Update position
    Position->x = length * std::sin(angle);
    Position->y = -length * std::cos(angle);
    
    // Update velocity
    Velocity->x = angularVelocity * length * std::cos(angle);
    Velocity->y = angularVelocity * length * std::sin(angle);
}

Ball Ball::lerp(const Ball& a, const Ball& b, float t) {
    return Ball(
        a.getMass() + (b.getMass() - a.getMass()) * t,
        a.getRadius() + (b.getRadius() - a.getRadius()) * t,
        Vec3D::lerp(a.getPosition(), b.getPosition(), t),
        Vec3D::lerp(a.getVelocity(), b.getVelocity(), t)
    );
}