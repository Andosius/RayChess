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
    /// <summary>
    /// Calculates possible moves and eliminates the ones, that would put the player in check
    /// </summary>
    /// <param name="board">The chess board from Chess.hpp</param>
    /// <param name="targetIdx">The chess piece that got clicked on</param>
    /// <param name="targetCall">If we should eliminate moves, for the clicked piece only</param>
    /// <returns></returns>
    std::vector<int> GetMovementPositions(const std::array<ChessField, 64>& board, int targetIdx, bool targetCall);
}