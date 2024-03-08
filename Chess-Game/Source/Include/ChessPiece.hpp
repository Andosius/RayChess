#pragma once


// Local dependencies


// External dependencies


// Standard Library


//======================================


enum struct ChessPiece
{
    King = 0,
    Queen = 1,
    Rook = 2,
    Bishop = 3,
    Knight = 4,
    Pawn = 5
};

/// <summary>
/// Returns the chess piece type based on its char
/// </summary>
/// <param name="piece">The chess piece from FEN</param>
/// <returns>Element from ChessPiece</returns>
inline ChessPiece GetChessPieceType(char piece)
{
    ChessPiece result = {};

    switch (piece)
    {
    case 'k':
    case 'K':
        result = ChessPiece::King;
        break;
    case 'q':
    case 'Q':
        result = ChessPiece::Queen;
        break;
    case 'r':
    case 'R':
        result = ChessPiece::Rook;
        break;
    case 'b':
    case 'B':
        result = ChessPiece::Bishop;
        break;
    case 'n':
    case 'N':
        result = ChessPiece::Knight;
        break;
    case 'p':
    case 'P':
        result = ChessPiece::Pawn;
        break;
    }

    return result;
}