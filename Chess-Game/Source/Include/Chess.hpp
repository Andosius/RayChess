#pragma once


// Local dependencies
#include "GameState.hpp"
#include "ChessField.hpp"


// External dependencies


// Standard Library
#include <array>

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

private:
    GameState m_GameState;
    std::array<ChessField, 64> m_Board;

    Texture2D m_BoardTexture;

    Color m_ColorBlack;
    Color m_ColorWhite;
    Color m_ColorSelected;
    Color m_ColorMove;
    Color m_ColorLastMove;
};