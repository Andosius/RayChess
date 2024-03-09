#pragma once


// Local dependencies
#include "ChessTeam.hpp"
#include "ChessPieceType.hpp"

// External dependencies


// Standard Library


//======================================


namespace Helpers
{
    ChessTeam GetChessPieceColor(char piece);

    /// <summary>
    /// Returns the chess piece type based on its char
    /// </summary>
    /// <param name="piece">The chess piece from FEN</param>
    /// <returns>Element from ChessPiece</returns>
    ChessPieceType GetChessPieceType(char piece);

    bool IsChessPiece(char piece);
    bool IsSameTeam(char piece, ChessTeam team);
}