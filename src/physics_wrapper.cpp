#include <emscripten/bind.h>
#include "Ball.h"
#include "Vec3D.h"
#include "RigidBody.h"

using namespace emscripten;

Vec3D add(const Vec3D& a, const Vec3D& b) { return a + b; }
Vec3D subtract(const Vec3D& a, const Vec3D& b) { return a - b; }
Vec3D multiply(const Vec3D& a, float scalar) { return a * scalar; }
Vec3D divide(const Vec3D& a, float scalar) { return a / scalar; }
Vec3D normalize(const Vec3D& v) { return v.normalize(); }
float distance(const Vec3D& a, const Vec3D& b) { return a.distance(b); }
Vec3D lerp(const Vec3D& a, const Vec3D& b, float t) { return a + (b - a) * t; }
float dot(const Vec3D& a, const Vec3D& b) { return a.dot(b); }
Vec3D cross(const Vec3D& a, const Vec3D& b) { return a.cross(b); }
float magnitude(const Vec3D& v) { return v.magnitude(); }

void updatePendulum(Ball& ball, float dt, float length, float gravity) {
    ball.updatePendulum(dt, length, gravity);
}

bool isColliding(const Ball& ball1, const Ball& ball2) {
    return ball1.isColliding(ball2);
}

void handleCollision(Ball& ball1, Ball& ball2) {
    ball1.handleCollision(ball2);
}

float getBallRadius(const Ball& ball) {
    return ball.getRadius();
}

void setBallRadius(Ball& ball, float radius) {
    ball.setRadius(radius);
}

Vec3D getBallPosition(const Ball& ball) {
    return ball.getPosition();
}

Vec3D getBallVelocity(const Ball& ball) {
    return ball.getVelocity();
}

void setBallPosition(Ball& ball, const Vec3D& pos) {
    ball.setPosition(pos);
}

void setBallVelocity(Ball& ball, const Vec3D& vel) {
    ball.setVelocity(vel);
}

float getBallMass(const Ball& ball) {
    return ball.getMass();
}

Ball lerpBall(const Ball& a, const Ball& b, float t) {
    return Ball::lerp(a, b, t);
}


EMSCRIPTEN_BINDINGS(physics_module) {
    function("add", &add);
    function("subtract", &subtract);
    function("multiply", &multiply);
    function("divide", &divide);
    function("normalize", &normalize);
    function("distance", &distance);
    function("lerp", &lerp);
    function("dot", &dot);
    function("cross", &cross);
    function("magnitude", &magnitude);

    function("isColliding", &isColliding);
    function("handleCollision", &handleCollision);
    function("getBallRadius", &getBallRadius);
    function("getBallPosition", &getBallPosition);
    function("getBallVelocity", &getBallVelocity);
    function("setBallRadius", &setBallRadius);
    function("setBallPosition", &setBallPosition);
    function("setBallVelocity", &setBallVelocity);
    function("getBallMass", &getBallMass);
    function("lerpBall", &lerpBall);

    class_<RigidBody>("RigidBody")
        .constructor<float, const Vec3D&, const Vec3D&>()
        .constructor<float>()
        .function("updateRK4", &RigidBody::updateRK4)
        .function("updatePendulum", &RigidBody::updatePendulum);

    class_<Vec3D>("Vec3D")
        .constructor<float, float, float>()
        .property("x", &Vec3D::x)
        .property("y", &Vec3D::y)
        .property("z", &Vec3D::z);

    class_<Ball>("Ball")
        .constructor<float, float, const Vec3D&, const Vec3D&>()
        .constructor<float, float>();
}