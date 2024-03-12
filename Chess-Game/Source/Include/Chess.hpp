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

    void DrawChessBoard();
    void HandleInput();

private:
    void GameStateToBoard();
    void GenerateBoardTexture();

    void OnPlayerLeftClickBoard(Vec2 position, bool isChessPiece);
    void OnPlayerReleaseLeftClickBoard(Vec2 position, bool isPossibleMove);
    void OnPlayerRightClickBoard(Vec2 position);

    void OnMoveHappened(Vec2 from, Vec2 to);

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

    bool m_IsMoving;

    int m_TargetPiece;
    std::vector<int> m_SelectedPositions;
    std::vector<int> m_PossibleMoves;
};

extern Chess* g_Chess;