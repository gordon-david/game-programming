#include "Vec4.h"

// #include "Mat4.h"



namespace Math
{

    Vec4::Vec4()
    {
        x = 0.0f;
        y = 0.0f;
    }

    Vec4::Vec4(const float x, const float y, const float z, const float w)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }
    Vec4 &Vec4::add(const Vec4 &other)
    {
        this->x += other.x;
        this->y += other.y;
        this->z += other.z;
        this->w += other.w;

        return *this;
    }

    Vec4 &Vec4::subtract(const Vec4 &other)
    {
        this->x -= other.x;
        this->y -= other.y;
        this->z -= other.z;
        this->w -= other.w;

        return *this;
    }

    Vec4 &Vec4::multiply(const Vec4 &other)
    {
        this->x *= other.x;
        this->y *= other.y;
        this->z *= other.z;
        this->w *= other.w;

        return *this;
    }
    Vec4 &Vec4::divide(const Vec4 &other)
    {
        this->x /= other.x;
        this->y /= other.y;
        this->z /= other.z;
        this->w /= other.w;

        return *this;
    }

    Vec4 Vec4::multiply(const struct Mat4 &transform)
    {
        return Vec4(
            transform.elements[0 + 0 * 4] * x + transform.elements[1 + 0 * 4] * y + transform.elements[2 + 0 * 4]* z + transform.elements[3 + 0 * 4] * w,
            transform.elements[0 + 1 * 4] * x + transform.elements[1 + 1 * 4] * y + transform.elements[2 + 1 * 4]* z + transform.elements[3 + 1 * 4] * w,
            transform.elements[0 + 2 * 4] * x + transform.elements[1 + 2 * 4] * y + transform.elements[2 + 2 * 4]* z + transform.elements[3 + 2 * 4] * w,
            transform.elements[0 + 3 * 4] * x + transform.elements[1 + 3 * 4] * y + transform.elements[2 + 3 * 4]* z + transform.elements[3 + 3 * 4] * w
            );
            // transform.elements[] columns[1].x * x + transform.columns[1].y * y + transform.columns[1].z * z + transform.columns[1].w * w,
            // transform.elements[] columns[2].x * x + transform.columns[2].y * y + transform.columns[2].z * z + transform.columns[2].w * w,
            // transform.elements[] columns[3].x * x + transform.columns[3].y * y + transform.columns[3].z * z + transform.columns[3].w * w
    }

    Vec4 operator+(Vec4 left, const Vec4 &right)
    {
        return left.add(right);
    }

    Vec4 operator-(Vec4 left, const Vec4 &right)
    {
        return left.subtract(right);
    }

    Vec4 operator*(Vec4 left, const Vec4 &right)
    {
        return left.multiply(right);
    }

    Vec4 operator/(Vec4 left, const Vec4 &right)
    {
        return left.divide(right);
    }

    Vec4 &Vec4::operator+=(const Vec4 &other)
    {
        return add(other);
    }

    Vec4 &Vec4::operator-=(const Vec4 &other)
    {
        return subtract(other);
    }
    Vec4 &Vec4::operator*=(const Vec4 &other)
    {
        return multiply(other);
    }
    Vec4 &Vec4::operator/=(const Vec4 &other)
    {
        return divide(other);
    }
    std::ostream &operator<<(std::ostream &stream, const Vec4 &vector)
    {
        stream << "Vec4: (" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << ")";
        return stream;
    }
    bool Vec4::operator==(const Vec4 &other)
    {
        return x == other.x && y == other.y && z == other.z && w == other.w;
    }
    bool Vec4::operator!=(const Vec4 &other)
    {
        return !(*this == other);
    }
}
