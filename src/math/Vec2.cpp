#include "Vec2.h"

namespace Math
{

	Vec2::Vec2()
	{
		x = 0.0f;
		y = 0.0f;
	}

	Vec2::Vec2(const float x, const float y)
	{
		this->x = x;
		this->y = y;
	}
	Vec2 &Vec2::add(const Vec2 &other)
	{
		this->x += other.x;
		this->y += other.y;

		return *this;
	}

	Vec2 &Vec2::subtract(const Vec2 &other)
	{
		this->x -= other.x;
		this->y -= other.y;

		return *this;
	}

	Vec2 &Vec2::multiply(const Vec2 &other)
	{
		this->x *= other.x;
		this->y *= other.y;

		return *this;
	}
	Vec2 &Vec2::divide(const Vec2 &other)
	{
		this->x /= other.x;
		this->y /= other.y;

		return *this;
	}

	Vec2 operator+(Vec2 left, const Vec2 &right)
	{
		return left.add(right);
	}

	Vec2 operator-(Vec2 left, const Vec2 &right)
	{
		return left.subtract(right);
	}

	Vec2 operator*(Vec2 left, const Vec2 &right)
	{
		return left.multiply(right);
	}

	Vec2 operator/(Vec2 left, const Vec2 &right)
	{
		return left.divide(right);
	}

	Vec2 &Vec2::operator+=(const Vec2 &other)
	{
		return add(other);
	}

	Vec2 &Vec2::operator-=(const Vec2 &other)
	{
		return subtract(other);
	}
	Vec2 &Vec2::operator*=(const Vec2 &other)
	{
		return multiply(other);
	}
	Vec2 &Vec2::operator/=(const Vec2 &other)
	{
		return divide(other);
	}
	std::ostream &operator<<(std::ostream &stream, const Vec2 &vector)
	{
		stream << "Vec2: (" << vector.x << ", " << vector.y << ")";
		return stream;
	}
	bool Vec2::operator==(const Vec2& other)
	{
		return x == other.x && y == other.y;
	}
	bool Vec2::operator!=(const Vec2& other)
	{
		return !(*this == other);
	}
}
