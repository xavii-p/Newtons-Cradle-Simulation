#include <vector>


class 404Engine{

    private:
        std::vector<RigidBody*> bodies;
        Vec3D m_gravity = Vec3D(0, -9.81f, 0);

    public:
        void addBody(RigidBody body) {
            r_bodies.push_back(body);
        }
        void removeBody(RigidBody body) {

        }

        void simulate(float dt) {
            for (RigidBody* body : bodies){
                body->applyForce(m_gravity);
                body->update(dt);


            }
        }
}