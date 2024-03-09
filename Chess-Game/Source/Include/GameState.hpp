#pragma once


// Local dependencies
#include "ChessTeam.hpp"
#include "Vector2.hpp"

// External dependencies


// Standard Library
#include <string>

//======================================


struct GameState
{
    GameState() = delete;
    GameState(const std::string& fen);

    std::string Export();


    std::string FenPieceMap = "";

    ChessTeam Turn = ChessTeam::White;

    bool WhiteCastlingKing = false;
    bool WhiteCastlingQueen = false;
    bool BlackCastlingKing = false;
    bool BlackCastlingQueen = false;

    Vec2 EnPassant = Vec2(-1, -1);

    int HalfMoveCounter = 0;
    int FullMoveEnumerator = 0;
};
