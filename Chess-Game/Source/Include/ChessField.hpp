#pragma once


// Local dependencies


// External dependencies
#include <raylib.h>

// Standard Library
#include <string>

//======================================


struct ChessField
{
    ChessField();
    ChessField(Color color, char piece);

    void AddSpecialColor(Color color);
    Color GetSpecialColor();
    void ResetSpecialColor();

    char Piece;
    Color FieldColor = WHITE;

    int R = 0;
    int G = 0;
    int B = 0;
    int A = 0;

    int ColorCount = 0;
};
