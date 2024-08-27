
#include "Engine.h"
#include "RigidBody.h"
#include "Vec3D.h"
#include <algorithm>

class Vec3D;

 void Engine::addBody(RigidBody* body) {
    bodies.push_back(body);
 }
 void Engine::removeBody(RigidBody* body) {
   bodies.erase(std::remove(bodies.begin(), bodies.end(), body), bodies.end());
 }

 void Engine::simulate(float dt) {
    for (RigidBody* body : bodies){
        body->applyForce(*new Vec3D(0.0f, -9.81f, 0.0f));
        body->update(dt);

     }
 }