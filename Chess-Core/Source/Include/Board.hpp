#pragma once

// Local dependencies
#include "Vector2.hpp"
#include "Definitions.hpp"

// External dependencies
#include <raylib.h>

// Standard Library
#include <vector>
#include <string>

//======================================


class Board
{
public:
	Board();
	~Board();
	
	void SetBoardColors();
	void ConfigureByFen(const size_t index);

	void DrawBoard();
	void DrawPieces();

	void HandleEvents();


private:

	std::vector<Vec2> m_Moves;
	std::vector<std::string> m_Fen;
	size_t m_FenIndex;

	GameState m_GameState;

	Color BoardColors[8][8];

	Vec2 m_SelectedPos;
};