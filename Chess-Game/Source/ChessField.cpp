#pragma once


// Local dependencies
#include "ChessField.hpp"

// External dependencies


// Standard Library


//======================================


ChessField::ChessField()
{
    Piece = ' ';
}

ChessField::ChessField(Color color, char piece)
{
    FieldColor = color;
    Piece = piece;
}

void ChessField::AddSpecialColor(Color color)
{
    R += color.r;
    G += color.g;
    B += color.b;
    A += color.a;
    ColorCount += 1;

    Color col = {};
    col.r = R / ColorCount;
    col.g = G / ColorCount;
    col.b = B / ColorCount;
    col.a = A / ColorCount;
}

Color ChessField::GetSpecialColor()
{
    Color col = {};
    col.r = R / ColorCount;
    col.g = G / ColorCount;
    col.b = B / ColorCount;
    col.a = A / ColorCount;

    return col;
}

void ChessField::ResetSpecialColor()
{
    R = 0;
    G = 0;
    B = 0;
    A = 0;
    ColorCount = 0;
}
