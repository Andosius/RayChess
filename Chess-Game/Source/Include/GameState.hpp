#pragma once


// Local dependencies
#include "ChessColor.hpp"
#include "Vector2.hpp"

// External dependencies


// Standard Library
#include <string>

//======================================


struct GameState
{
    GameState() = delete;
    GameState(const std::string& fen);


    std::string FenPieceMap = "";

    ChessColor Turn = ChessColor::White;

    bool WhiteCastlingQueen = false;
    bool WhiteCastlingKing = false;
    bool BlackCastlingQueen = false;
    bool BlackCastlingKing = false;

    Vec2 EnPassant = Vec2(-1, -1);

    int HalfMoveCounter = 0;
    int FullMoveEnumerator = 0;
};
