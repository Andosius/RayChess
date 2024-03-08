#pragma once


// Local dependencies
#include "GameState.hpp"

// External dependencies


// Standard Library
#include <string>

//======================================


namespace Utility
{
    /// <summary>
    /// Checks if a char is a number.
    /// </summary>
    /// <param name="data">The char to check</param>
    /// <returns>true if data greater or equal 48 and smaller or equal 57</returns>
    bool IsCharNumber(char data);

    /// <summary>
    /// Converts a char to integer number
    /// </summary>
    /// <param name="data">The char to convert to an integer</param>
    /// <returns>int for the number that is the result of value(data) - 48</returns>
    int ConvertCharToNumber(char data);
}
