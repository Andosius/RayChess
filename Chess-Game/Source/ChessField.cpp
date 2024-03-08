#pragma once


// Local dependencies
#include "ChessField.hpp"

// External dependencies


// Standard Library


//======================================


ChessField::ChessField()
{
    FieldColor = WHITE;
    Piece = ' ';
}

ChessField::ChessField(Color color, char piece)
{
    FieldColor = color;
    Piece = piece;
}
