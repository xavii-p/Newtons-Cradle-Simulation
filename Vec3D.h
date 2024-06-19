
struct Vec3D {
    
        float x;
        float y;
        float z;

        Vec3(float x_val, float y_val, float z_val){
            x = x_val;
            y = y_val;
            z = z_val;
        }

        float magnitude() const{
            return std::sqrt(x * x + y * y + z * z);
        }

        Vector3D operator+(const Vector3D& other) const {
        return Vector3D(x + other.x, y + other.y, z other.z);
    }

        Vector3D operator*(float scalar) const {
            return Vector3D(x * scalar, y * scalar, z * scalar);
        }

        Vector3D operator/(float scalar) const {
            return Vector3D(x / scalar, y / scalar, z / scalar);
        }
}