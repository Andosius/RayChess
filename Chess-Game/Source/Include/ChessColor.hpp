#pragma once


// Local dependencies


// External dependencies


// Standard Library


//======================================


enum struct ChessColor
{
    Black = 0,
    White = 1
};


inline ChessColor GetChessPieceColor(char piece)
{
    if (piece >= 97 && piece <= 122)
    {
        return ChessColor::White;
    }
    else
    {
        return ChessColor::Black;
    }
}