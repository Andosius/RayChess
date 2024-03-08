// Local dependencies
#include "Utility.hpp"

// External dependencies


// Standard Library
#include <array>
#include <sstream>

//======================================


namespace Utility
{
    bool IsCharNumber(char data)
    {
        return data >= 48 && data <= 57;
    }

    int ConvertCharToNumber(char data)
    {
        return static_cast<int>(data - 48);
    }
}
