#pragma once

struct Vec2
{
	float x;
	float y;

	Vec2() : x(0), y(0)
	{
	}

	Vec2(float x, float y) : x(x), y(y)
	{
	}

	Vec2 operator+(const Vec2& other)
	{
		return Vec2(x + other.x, y + other.y);
	}

	Vec2& operator+=(const Vec2& other)
	{
		x += other.x;
		y += other.y;

		return *this;
	}

	Vec2 operator-(const Vec2& other)
	{
		return Vec2(x - other.x, y - other.y);
	}

	Vec2& operator-=(const Vec2& other)
	{
		x -= other.x;
		y -= other.y;

		return *this;
	}

	template <typename T>
	Vec2 operator*(const T& num)
	{
		return Vec2(x * num, y * num);
	}

	template <typename T>
	Vec2& operator*=(const T& num)
	{
		x *= num;
		y *= num;

		return *this;
	}

	template <typename T>
	Vec2 operator/(const T& num)
	{
		assert(0 != num && "Vector cannot divide by 0");
		return Vec2(x / num, y / num);
	}

	template <typename T>
	Vec2& operator/=(const T& num)
	{
		assert(0 != num && "Vector cannot divide by 0");
		x /= num;
		y /= num;

		return *this;
	}
};