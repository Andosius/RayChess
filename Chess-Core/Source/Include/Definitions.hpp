#pragma once

// Local dependencies


// External dependencies
#include <raylib.h>

// Standard Library
#include <string>

//======================================


constexpr int FIELD_WIDTH = 100;
constexpr int PIECE_OFFSET = 10; // (FIELD_WIDTH - 80) (PNG-Size) / 2

constexpr Color COLORFUL_PIECE_COLOR = Color{ 188, 210, 14, 255 };
constexpr Color WHITE_PIECE_COLOR = Color{ 255, 255, 255, 255 };
constexpr Color SELECTED_PIECE_COLOR = GREEN;
constexpr Color POSSIBLE_MOVE_COLOR = RED;

const std::string DEFAULT_FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

enum ChessPieceIndex
{
	KingBlack = 0,
	KingWhite = 1,
	QueenBlack = 2,
	QueenWhite = 3,
	RookBlack = 4,
	RookWhite = 5,
	BishopBlack = 6,
	BishopWhite = 7,
	KnightBlack = 8,
	KnightWhite = 9,
	PawnBlack = 10,
	PawnWhite = 11
};

enum ChessPieceType
{
	King = 0,
	Queen = 1,
	Rook = 2,
	Bishop = 3,
	Knight = 4,
	Pawn = 5
};

enum struct ChessColor
{
	Black = 0,
	White = 1
};

struct DrawData
{
	int PixelX;
	int PixelY;

	int TextureIndex;

	DrawData(int x, int y, int idx)
		: PixelX(x), PixelY(y), TextureIndex(idx)
	{
	}
};

struct GameState
{
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
