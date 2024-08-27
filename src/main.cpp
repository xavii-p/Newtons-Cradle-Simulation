#include <iostream>
#include "Engine.h"
#include "RigidBody.h"
#include "Vec3D.h"

int main(){
    Vec3D position(0.0f, 0.0f, 0.0f);
    Vec3D velocity(1.0f, 1.0f, 1.0f);
    int run = 1;

    // body w/ specified pos. and vel.
    RigidBody body(1.0f, &position, &velocity);

    // random stationary body
    RigidBody body2(4.0f);

    std::cout << "Position of random body ( " << body.getPosition().x << ", " << body.getPosition().y << ", " << body.getPosition().z << ")";

    Engine engine;
    engine.addBody(&body);
    int i = 0;
    
    while(run < 10) {
        engine.simulate(1.0f);
        std::cout << "Position after " << (i + 1) << " seconds: (" << body.getPosition().x << ", " << body.getPosition().y << ")\n";
        i++;
        run++;    
    }

    return 0;
}