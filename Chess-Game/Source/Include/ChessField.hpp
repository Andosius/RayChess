#pragma once


// Local dependencies


// External dependencies
#include <raylib.h>

// Standard Library
#include <string>

//======================================


struct ChessField
{
    ChessField() = default;
    ChessField(Color color, char piece);

    Color FieldColor;
    char Piece;
};