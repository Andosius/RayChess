#pragma once


// Local dependencies
#include "ChessField.hpp"
#include "ChessTeam.hpp"

// External dependencies


// Standard Library
#include <vector>
#include <array>

//======================================


namespace Move
{
    std::vector<int> GetMovementPositions(const std::array<ChessField, 64>& board, int targetIdx, bool targetCall);
}