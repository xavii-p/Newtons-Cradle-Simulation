
class RigidBody {
    private:

        float Mass;
        Vec3D* Position; // 3 dimensional vector w/ floats: <x, y, z> 
        Vec3D* Velocity;
        Vec3D* Force;

    public:
        RigidBody(float m, Vec3D* pos, Vec3D* vel){
            Mass = m;
            Position = pos;
            Velocity = vel;
            
        }

        void applyForce(const Vec3D& force) {
            // simplified F = ma
            Vec3D acceleration = force / Mass;
            *Velocity = *Velocity + acceleration;
        }

        void update(float dt) {
            // simplified x = x_o + vt
            *Position = *Position + (*Velocity * dt);
        }

        Vec3D getPosition() const {
            return *Position;
        }

}