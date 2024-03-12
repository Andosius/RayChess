#pragma once


// Local dependencies


// External dependencies


// Standard Library
#include <cmath>

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

    /// <summary>
    /// Gets the distance between two vectors.
    /// </summary>
    /// <param name="first">First vector</param>
    /// <param name="second">Second vector</param>
    /// <returns>int The distance between them</returns>
    static int GetDistance(const Vec2 first, const Vec2 second)
    {
        int deltaX = second.X - first.X;
        int deltaY = second.Y - first.Y;

        return static_cast<int>(std::sqrt((deltaX * deltaX) + (deltaY * deltaY)));
    }

    /// <summary>
    /// Checks for valid chess board positions.
    /// </summary>
    /// <returns>True if X and Y are >= 0 and < 8</returns>
    bool IsValidPosition() const
    {
        return X >= 0 && X < 8 && Y >= 0 && Y < 8;
    }

    /// <summary>
    /// Converts Vec2 to integer index with default base 8.
    /// </summary>
    /// <param name="base">The base to multiply Y with</param>
    /// <returns>int The index</returns>
    int ToInt(int base = 8) const
    {
        return Y * base + X;
    }

    /// <summary>
    /// Adds two Vec2 together.
    /// </summary>
    /// <param name="other">The other Vec2 we want to add to a result</param>
    /// <returns>Vec2 The result</returns>
    Vec2 operator+(const Vec2 other) const
    {
        Vec2 result;

        result.X = other.X + X;
        result.Y = other.Y + Y ;

        return result;
    }

    /// <summary>
    /// Multiplies the values of the original vector with the multiplier Vec2.
    /// Useful for directions like `Vec2(0, 1)` for going down.
    /// </summary>
    /// <param name="multiplier">Contains values for X and Y multiplication.</param>
    /// <returns>Vec2 The result</returns>
    Vec2 operator*(const Vec2 multiplier) const
    {
        Vec2 result = *this;
        result.X *= multiplier.X;
        result.Y *= multiplier.Y;

        return result;
    }

    /// <summary>
    /// Multiplies the value of X and Y by multiplier.
    /// </summary>
    /// <param name="multiplier">The integer to multiply against</param>
    /// <returns>Vec2 The result</returns>
    Vec2 operator*(const int multiplier) const
    {
        Vec2 result = *this;
        result.X *= multiplier;
        result.Y *= multiplier;

        return result;
    }

    /// <summary>
    /// Compares two Vec2.
    /// </summary>
    /// <param name="data">The Vec2 we compare against</param>
    /// <returns>True if X and Y are the same</returns>
    bool operator==(const Vec2 data) const
    {
        return data.X == X && data.Y == Y;
    }
};
