#pragma once


// Local dependencies
#include "ChessTeam.hpp"
#include "ChessPieceType.hpp"

// External dependencies


// Standard Library


//======================================


namespace Helpers
{
    /// <summary>
    /// Find the chess pieces team by checking for lower or uppercase letters.
    /// </summary>
    /// <param name="piece">The chess piece we check</param>
    /// <returns>ChessTeam The color of the piece (white or black)</returns>
    ChessTeam GetChessPieceColor(char piece);

    /// <summary>
    /// Returns the chess piece type based on its char
    /// </summary>
    /// <param name="piece">The chess piece from FEN</param>
    /// <returns>Element from ChessPiece</returns>
    ChessPieceType GetChessPieceType(char piece);

    /// <summary>
    /// Checks for != ' ' to identify chess pieces.
    /// </summary>
    /// <param name="piece">The chess piece we check</param>
    /// <returns>True If piece != ' '</returns>
    bool IsChessPiece(char piece);

    /// <summary>
    /// Checks if the pieces are in the same team.
    /// </summary>
    /// <param name="piece">The chess piece we check</param>
    /// <param name="team">The original pieces team color</param>
    /// <returns>True If piece-team == team</returns>
    bool IsSameTeam(char piece, ChessTeam team);
}
