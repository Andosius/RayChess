#pragma once


// Local dependencies
#include "GameState.hpp"
#include "ChessField.hpp"


// External dependencies


// Standard Library
#include <array>
#include <vector>

//======================================


class Chess
{
public:
    Chess();
    ~Chess();

    Chess(const Chess&) = delete;
    Chess(Chess&&) = delete;

    void GameStateToBoard();
    void GenerateBoardTexture();

    void DrawChessBoard();
    void HandleInput();

private:
    bool IsPiecesTurn(char piece);

public:
    GameState State;
    std::array<ChessField, 64> Board;

private:
    Texture2D m_BoardTexture;

    Color m_ColorBlack;
    Color m_ColorWhite;
    Color m_ColorSelected;
    Color m_ColorMove;
    Color m_ColorLastMove;
    Color m_ColorMarked;

    int m_TargetPiece;
    std::vector<int> m_SelectedPositions;
    std::vector<int> m_PossibleMoves;
};