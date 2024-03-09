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

    Vec2(int n)
    {
        X = n % 8;
        Y = n / 8;
    }

    ~Vec2() = default;

    bool IsValidPosition() const
    {
        return X >= 0 && X < 8 && Y >= 0 && Y < 8;
    }

    int ToInt(int base = 8) const
    {
        return Y * base + X;
    }

    Vec2 operator+(const Vec2 other) const
    {
        Vec2 result;

        result.X = other.X + X;
        result.Y = other.Y + Y ;

        return result;
    }
    
    Vec2 operator*(const Vec2 multiplier) const
    {
        Vec2 result = *this;
        result.X *= multiplier.X;
        result.Y *= multiplier.Y;

        return result;
    }

    Vec2 operator*(const int multiplier) const
    {
        Vec2 result = *this;
        result.X *= multiplier;
        result.Y *= multiplier;

        return result;
    }

    bool operator==(const Vec2 data) const
    {
        return data.X == X && data.Y == Y;
    }
};
