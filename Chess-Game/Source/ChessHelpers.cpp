#pragma once


// Local dependencies
#include "ChessHelpers.hpp"

// External dependencies


// Standard Library


//======================================


namespace Helpers
{
    ChessTeam GetChessPieceColor(char piece)
    {
        if (piece >= CHAR_LOWER_START && piece <= CHAR_LOWER_END)
        {
            return ChessTeam::Black;
        }
        else
        {
            return ChessTeam::White;
        }
    }

    ChessPieceType GetChessPieceType(char piece)
    {
        ChessPieceType result = {};

        switch (piece)
        {
        case 'k':
        case 'K':
            result = ChessPieceType::King;
            break;
        case 'q':
        case 'Q':
            result = ChessPieceType::Queen;
            break;
        case 'r':
        case 'R':
            result = ChessPieceType::Rook;
            break;
        case 'b':
        case 'B':
            result = ChessPieceType::Bishop;
            break;
        case 'n':
        case 'N':
            result = ChessPieceType::Knight;
            break;
        case 'p':
        case 'P':
            result = ChessPieceType::Pawn;
            break;
        }

        return result;
    }

    bool IsChessPiece(char piece)
    {
        return piece != ' ';
    }

    bool IsSameTeam(char piece, ChessTeam team)
    {
        return GetChessPieceColor(piece) == team;
    }

    int GetTeamKing(const std::array<ChessField, 64>& board, ChessTeam team)
    {
        const auto it = std::find_if(board.begin(), board.end(),
            [&](const ChessField& element)
            {
                return (team == ChessTeam::Black && element.Piece == 'k') || team == ChessTeam::White && element.Piece == 'K';
            });

        return (int)std::distance(board.begin(), it);
    }
}