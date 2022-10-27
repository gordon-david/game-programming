#include "Mat4.h"

#include <math.h>

namespace Math
{
    Mat4::Mat4()
    {
        for (int i = 0; i < 4 * 4; i++)
            elements[i] = 0.0f;
    }

    // TODO: test, should optimize during compiling
    Mat4::Mat4(float diagonal)
    {
        for (int i = 0; i < 4 * 4; i++)
            elements[i] = 0.0f;

        elements[0 + 0 * 4] = diagonal;
        elements[1 + 1 * 4] = diagonal;
        elements[2 + 2 * 4] = diagonal;
        elements[3 + 3 * 4] = diagonal;
    }

    Mat4 Mat4::identity()
    {
        return Mat4(1.0f);
    }

    // column major (used by opengl, and therefore us: e[row + (col * 4)]
    Mat4 &Mat4::multiply(const Mat4 &other)
    {
        for (int y = 0; y < 4; y++)
        {
            for (int x = 0; x < 4; x++)
            {
                float sum = 0.0f;
                for (int e = 0; e < 4; e++)
                {
                    sum += elements[x + e * 4] * other.elements[e + y * 4];
                }
                elements[x + y * 4] = sum;
            }
        }

        return *this;
    }

    std::ostream &operator<<(std::ostream &stream, const Mat4 &matrix)
    {
        stream
            << matrix.elements[0 + 0 * 4] << " " << matrix.elements[0 + 1 * 4] << " " << matrix.elements[0 + 2 * 4] << " " << matrix.elements[0 + 3 * 4] << " " << std::endl
            << matrix.elements[1 + 0 * 4] << " " << matrix.elements[1 + 1 * 4] << " " << matrix.elements[1 + 2 * 4] << " " << matrix.elements[1 + 3 * 4] << " " << std::endl
            << matrix.elements[2 + 0 * 4] << " " << matrix.elements[2 + 1 * 4] << " " << matrix.elements[2 + 2 * 4] << " " << matrix.elements[2 + 3 * 4] << " " << std::endl
            << matrix.elements[3 + 0 * 4] << " " << matrix.elements[3 + 1 * 4] << " " << matrix.elements[3 + 2 * 4] << " " << matrix.elements[3 + 3 * 4] << " " << std::endl;

        return stream;
    }

    Mat4
    operator*(Mat4 left, const Mat4 &right)
    {
        return left.multiply(right);
    }

    Mat4 &Mat4::operator+=(const Mat4 &other)
    {
        return multiply(other);
    }

    Mat4 Mat4::orthographic(float left, float right, float bottom, float top, float near, float far)
    {
        Mat4 result(1.0f);
        //             [row + colum * 4]
        result.elements[0 + 0 * 4] = 2.0f / (right - left);
        result.elements[1 + 1 * 4] = 2.0f / (top - bottom);
        result.elements[2 + 2 * 4] = -2.0f / (far - near);
        result.elements[0 + 3 * 4] = -(right + left) / (right - left);
        result.elements[1 + 3 * 4] = -(top + bottom) / (top - bottom);
        result.elements[2 + 3 * 4] = -(far + near) / (far - near);

        return result;
    }

    Mat4 Mat4::orthographic_inverse(float left, float right, float bottom, float top, float near, float far)
    {

        Mat4 result(1.0f);
        //             [row + column * 4]
        result.elements[0 + 0 * 4] = (right - left) / 2.0f;
        result.elements[1 + 1 * 4] = (top - bottom) / 2.0f;
        result.elements[2 + 2 * 4] = (far - near) / -2.0f;
        result.elements[0 + 3 * 4] = (right + left) / 2.0f;
        result.elements[1 + 3 * 4] = (top + bottom) / 2.0f;
        result.elements[2 + 3 * 4] = -(far + near) / 2.0f;

        return result;
    }

    Mat4 Mat4::perspective(float fov, float aspectRatio, float near, float far)
    {
        float fov_radians = Math::toRadians(fov);
        float tanResult = tan(fov_radians / 2.0f);
        Mat4 result(1.0f);

        //             [row + colum * 4]
        result.elements[0 + 0 * 4] =  1.0f / (aspectRatio * tanResult);
        result.elements[1 + 1 * 4] =  1.0f / (tanResult);
        result.elements[2 + 2 * 4] = -(far + near) / (far - near);
        result.elements[3 + 3 * 4] =  0.0f;
        result.elements[3 + 2 * 4] = -1.0f;
        result.elements[2 + 3 * 4] = -(2.0f * far * near) / (far - near);

        return result;
    }

    // identity matrix with top elements of last column setting x, y, z for translation
    Mat4 Mat4::translation(const struct Vec3 &translation)
    {
        Mat4 result(1.0f);

        result.elements[0 + 3 * 4] = translation.x;
        result.elements[1 + 3 * 4] = translation.y;
        result.elements[2 + 3 * 4] = translation.z;

        return result;
    }

    Mat4 Mat4::scale(const struct Vec3 &scale)
    {
        Mat4 result(1.0f);

        result.elements[0 + 0 * 4] = scale.x;
        result.elements[1 + 1 * 4] = scale.y;
        result.elements[2 + 2 * 4] = scale.z;

        return result;
    }

    Mat4 Mat4::rotation(float angle, const struct Vec3 axis)
    {
        Mat4 result(1.0f);

        float r = Math::toRadians(angle);
        float c = cos(r);
        float s = sin(r);
        float omc = 1.0f - c;

        float x = axis.x;
        float y = axis.y;
        float z = axis.z;

        result.elements[0 + 0 * 4] = x * x * omc + c;
        result.elements[0 + 1 * 4] = y * x * omc + z * s;
        result.elements[0 + 2 * 4] = x * z * omc - y * s;

        result.elements[1 + 0 * 4] = x * y * omc - z * s;
        result.elements[1 + 1 * 4] = y * y * omc + c;
        result.elements[1 + 2 * 4] = y * z * omc + x * s;

        result.elements[2 + 0 * 4] = x * z * omc + y * s;
        result.elements[2 + 1 * 4] = y * z * omc - x * s;
        result.elements[2 + 2 * 4] = z * z * omc + c;

        return result;
    }
}
