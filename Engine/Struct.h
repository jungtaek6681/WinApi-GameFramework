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

	Vec2 operator+(const Vec2& other) const
	{
		return Vec2(x + other.x, y + other.y);
	}

	Vec2& operator+=(const Vec2& other)
	{
		x += other.x;
		y += other.y;

		return *this;
	}

	Vec2 operator-(const Vec2& other) const
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
	Vec2 operator*(const T& num) const
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
	Vec2 operator/(const T& num) const
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

	float Magnitude() const
	{
		return sqrtf(x * x + y * y);
	}

	// 거리연산(피타고라스)의 루트연산이 굉장히 많은 시간을 요구하기 때문에
	// 거리의 차이만 비교하고 싶을 경우 루트연산을 하지 않은 길이의 제곱끼리 비교
	float SqrMagnitude() const
	{
		return x * x + y * y;
	}

	float Length() const
	{
		return Magnitude();
	}

	// 정규화(표준화) : 길이가 1인 백터(단위백터)로 변환
	// 방향성백터와 같이 길이가 1인 백터가 필요할 경우 변환
	void Normalize()
	{
		if (SqrMagnitude() == 0)
		{
			x = 0;
			y = 0;
		}
		else
		{
			float length = Length();
			x = x / length;
			y = y / length;
		}
	}

	// 단위백터를 반환
	Vec2 Normalized() const
	{
		if (SqrMagnitude() == 0)
		{
			return Vec2(0, 0);
		}
		else
		{
			float length = Length();
			return Vec2(x / length, y / length);
		}
	}
};