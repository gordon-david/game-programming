#pragma once

#include "Math.h"

// #include "Vec4.h"

namespace Math
{
    struct Mat4
    {
        // [row + column * 8]
        float elements[4 * 4];

        Mat4();
        Mat4(float diagonal);

        static Mat4 identity();

        Mat4 &multiply(const Mat4 &other);
        friend Mat4 operator*(Mat4 left, const Mat4 &right);
        Mat4 &operator+=(const Mat4 &other);

        friend std::ostream &operator<<(std::ostream &stream, const Mat4 &matrix);

        // Mat4 a = Mat4::identity() or ::projection()

        /*      positive
          left           right
                negative
            (screen, camera) => near->|   |<-far
        */
        static Mat4 orthographic(float left, float right, float bottom, float top, float near, float far);

        static Mat4 orthographic_inverse(float left, float right, float bottom, float top, float near, float far);

        /*
          near and far clipping, aspect ratio, field of view
        */
        static Mat4 perspective(float fov, float aspectRatio, float near, float far);

        static Mat4 translation(const struct Vec3 &translation);
        static Mat4 rotation(float angle, const struct Vec3 axis);
        static Mat4 scale(const struct Vec3 &scale);
    };
}