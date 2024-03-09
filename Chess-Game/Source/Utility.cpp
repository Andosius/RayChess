// Local dependencies
#include "Utility.hpp"
#include "Constants.hpp"

// External dependencies


// Standard Library
#include <array>
#include <sstream>

//======================================


namespace Utility
{
    bool IsCharNumber(char data)
    {
        return data >= CHAR_NUM_START && data <= CHAR_NUM_END;
    }

    int ConvertCharToNumber(char data)
    {
        return static_cast<int>(data - CHAR_TO_NUM_DIFF);
    }
}
