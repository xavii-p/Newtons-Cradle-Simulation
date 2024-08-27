
#ifndef ENGINE_H
#define ENGINE_H

class Vec3D;
class RigidBody;

#include <vector>

 


 class Engine {

    private:
        std::vector<RigidBody*> bodies;

    public:
        void addBody(RigidBody* body);

        void removeBody(RigidBody* body);

        void simulate(float dt);
 };
#endif