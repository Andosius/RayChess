#pragma once

// Local dependencies


// External dependencies


// Standard Library


//======================================


struct Vec2
{
	int X, Y;

	Vec2()
		: X(0), Y(0)
	{
	}

	Vec2(int x, int y)
		: X(x), Y(y)
	{
	}

	void TurnAround()
	{
		Y *= -1;
	}

	~Vec2() = default;

	bool IsValidPosition() const
	{
		return X >= 0 && X < 8 && Y >= 0 && Y < 8;
	}

	bool operator==(const Vec2 other) const
	{
		return (X == other.X) && (Y == other.Y);
	}

	bool operator!=(const Vec2 other) const
	{
		return (X != other.X) || (Y != other.Y);
	}

	Vec2 operator+(const Vec2 other)
	{
		Vec2 result;
		result.X = X + other.X;
		result.Y = Y + other.Y;
		return result;
	}

	Vec2 operator*(int multiplier)
	{
		Vec2 result = *this;
		result.X *= multiplier;
		result.Y *= multiplier;

		return result;
	}

	void operator<<(int n)
	{
		int count = (int)(*this) + n;

		X = count % 8;
		Y = count / 8;
	}

	operator int() const
	{
		return Y * 8 + X;
	}
};