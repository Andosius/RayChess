#pragma once

// Local dependencies
#include "Definitions.hpp"
#include "Vector2.hpp"

// External dependencies


// Standard Library
#include <string>

//======================================

namespace Utility
{
	inline int GetTextureIndex(char piece)
	{
		ChessPieceIndex idx{};

		switch (piece)
		{
		case 'r': idx = ChessPieceIndex::RookBlack; break;
		case 'n': idx = ChessPieceIndex::KnightBlack; break;
		case 'b': idx = ChessPieceIndex::BishopBlack; break;
		case 'q': idx = ChessPieceIndex::QueenBlack; break;
		case 'k': idx = ChessPieceIndex::KingBlack; break;
		case 'p': idx = ChessPieceIndex::PawnBlack; break;

		case 'R': idx = ChessPieceIndex::RookWhite; break;
		case 'N': idx = ChessPieceIndex::KnightWhite; break;
		case 'B': idx = ChessPieceIndex::BishopWhite; break;
		case 'Q': idx = ChessPieceIndex::QueenWhite; break;
		case 'K': idx = ChessPieceIndex::KingWhite; break;
		case 'P': idx = ChessPieceIndex::PawnWhite; break;
		}

		return idx;
	}

	inline bool IsCharNumber(char piece)
	{
		return piece >= 48 && piece <= 57;
	}

	inline int CharToNumber(char piece)
	{
		return (int)(piece - 48);
	}

	inline std::string FenToPieceMapString(const std::string& fen)
	{
		std::string result;

		int i = 0;
		while (fen[i] != ' ')
		{
			if (!IsCharNumber(fen[i]) && fen[i] != '/')
			{
				result += std::to_string(fen[i]);
			}
			else
			{
				for (int x = 0; x < Utility::CharToNumber(fen[i]); x++)
				{
					result += std::to_string(' ');
				}
			}

			i += 1;
		}

		return result;
	}

	inline ChessColor GetPiecesTeam(char piece)
	{
		if (piece >= 97 && piece <= 122)
		{
			return ChessColor::Black;
		}
		return ChessColor::White;
	}

	inline bool IsSameTeam(char pieceA, char pieceB)
	{
		// Same "team"
		// A-Z => 65-90 | a-z => 97-122
		if ((pieceA >= 65 && pieceA <= 90 && pieceB >= 65 && pieceB <= 90) || (pieceA >= 97 && pieceA <= 122 && pieceB >= 97 && pieceB <= 122))
		{
			return true;
		}
		
		return false;
	}
}

