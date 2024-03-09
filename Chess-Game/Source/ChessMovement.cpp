#pragma once


// Local dependencies
#include "ChessMovement.hpp"
#include "Vector2.hpp"
#include "ChessHelpers.hpp"

// External dependencies


// Standard Library
#include <string>
#include <set>
#include <chrono>

//======================================


namespace Move
{
    struct MoveInformation
    {
        MoveInformation(ChessPieceType type, ChessTeam team, Vec2 pos)
        {
            Type = type;
            Team = team;
            Position = pos;
        }

        ChessPieceType Type;
        ChessTeam Team;
        Vec2 Position;
    };

    static int GetTeamKing(const std::array<ChessField, 64>& board, ChessTeam team)
    {
        const auto it = std::find_if(board.begin(), board.end(),
            [&](const ChessField& element)
            {
                return (team == ChessTeam::Black && element.Piece == 'k') || team == ChessTeam::White && element.Piece == 'K';
            });

        return (int)std::distance(board.begin(), it);
    }

    static void GetContinuousPositions(std::vector<int>& moves, const std::array<ChessField, 64>& board, const MoveInformation& info, const Vec2 direction)
    {
        int multiplier = 1;

        while (true)
        {
            Vec2 test_pos = info.Position + (direction * multiplier);
            int test_idx = test_pos.ToInt();

            if (test_pos.IsValidPosition())
            {
                if (Helpers::IsChessPiece(board[test_idx].Piece))
                {
                    if (!Helpers::IsSameTeam(board[test_idx].Piece, info.Team))
                    {
                        moves.push_back(test_idx);
                    }
                    break;
                }
                else
                {
                    moves.push_back(test_idx);
                }
            }
            else
            {
                break;
            }

            multiplier++;
        }
    }

    static void GetPawnPositions(std::vector<int>& moves, const std::array<ChessField, 64>& board, const MoveInformation& info)
    {
        const Vec2 direction = (info.Team == ChessTeam::Black) ? Vec2(1, 1) : Vec2(1, -1);
        bool atStartPosition = (info.Team == ChessTeam::Black && info.Position.Y == 1) || (info.Team == ChessTeam::White && info.Position.Y == 6);

        const std::array<Vec2, 2> positions_take = {
            Vec2(-1, 1), // left diagonal
            Vec2(1, 1), // right diagonal
        };

        const std::array<Vec2, 2> positions_move = {
            Vec2(0, 1), // one up/down
            Vec2(0, 2) // two up/down
        };


        for (const Vec2 take : positions_take)
        {
            Vec2 test_pos = info.Position + (take * direction);
            int test_idx = test_pos.ToInt();

            if (test_pos.IsValidPosition() && Helpers::IsChessPiece(board[test_idx].Piece) && !Helpers::IsSameTeam(board[test_idx].Piece, info.Team))
            {
                moves.push_back(test_idx);
            }
        }

        for (const Vec2 take : positions_move)
        {
            Vec2 test_pos = info.Position + (take * direction);
            int test_idx = test_pos.ToInt();

            if (test_pos.IsValidPosition())
            {
                if (!Helpers::IsChessPiece(board[test_idx].Piece))
                {
                    moves.push_back(test_idx);
                }
                else
                {
                    break;
                }
            }
        }
    }

    static void GetKnightPositions(std::vector<int>& moves, const std::array<ChessField, 64>& board, const MoveInformation& info)
    {
        const std::array<Vec2, 8> positions = {
            // bottom left
            Vec2(-1, 2),   // one left, two down
            Vec2(-2, 1),   // two left, one down

            // top left
            Vec2(-1 , -2), // one left, two up
            Vec2(-2, -1),  // two left, one up

            // bottom right
            Vec2(1, 2),    // one right, two down
            Vec2(2, 1),    // two right, one down

            // top right
            Vec2(1, -2),   // one right, two up
            Vec2(2, -1),   // two right, one up
        };

        for (const Vec2 jump : positions)
        {
            Vec2 test_pos = info.Position + jump;
            int test_idx = test_pos.ToInt();

            if (test_pos.IsValidPosition() && (!Helpers::IsChessPiece(board[test_idx].Piece) || !Helpers::IsSameTeam(board[test_idx].Piece, info.Team)))
            {
                moves.push_back(test_idx);
            }
        }
    }

    static void GetRookPositions(std::vector<int>& moves, const std::array<ChessField, 64>& board, const MoveInformation& info)
    {
        const Vec2 left = Vec2(-1, 0);
        const Vec2 right = Vec2(1, 0);
        const Vec2 up = Vec2(0, -1);
        const Vec2 down = Vec2(0, 1);

        GetContinuousPositions(moves, board, info, left);
        GetContinuousPositions(moves, board, info, right);
        GetContinuousPositions(moves, board, info, up);
        GetContinuousPositions(moves, board, info, down);
    }

    static void GetBishopPositions(std::vector<int>& moves, const std::array<ChessField, 64>& board, const MoveInformation& info)
    {
        const Vec2 top_left = Vec2(-1, -1);
        const Vec2 top_right = Vec2(1, -1);
        const Vec2 bottom_left = Vec2(-1, 1);
        const Vec2 bottom_right = Vec2(1, 1);

        GetContinuousPositions(moves, board, info, top_left);
        GetContinuousPositions(moves, board, info, top_right);
        GetContinuousPositions(moves, board, info, bottom_left);
        GetContinuousPositions(moves, board, info, bottom_right);
    }

    static void GetQueenPositions(std::vector<int>& moves, const std::array<ChessField, 64>& board, const MoveInformation& info)
    {
        GetRookPositions(moves, board, info);
        GetBishopPositions(moves, board, info);
    }
    
    static void GetKingPositions(std::vector<int>& moves, const std::array<ChessField, 64>& board, const MoveInformation& info)
    {
        const std::array<Vec2, 8> positions = {
            Vec2(-1, -1), // top left
            Vec2(0, -1),  // top
            Vec2(1, -1),  // top right
            Vec2(1, 0),   // right
            Vec2(1, 1),   // bottom right
            Vec2(0, 1),   // bottom
            Vec2(-1, 1),  // bottom left
            Vec2(-1, 0)   // left
        };

        for (const Vec2 pos : positions)
        {
            Vec2 test_pos = info.Position + pos;
            int test_idx = test_pos.ToInt();

            if (test_pos.IsValidPosition() && (!Helpers::IsChessPiece(board[test_idx].Piece) || !Helpers::IsSameTeam(board[test_idx].Piece, info.Team)))
            {
                moves.push_back(test_idx);
            }
        }
    }

    static void EliminateCheckPositions(std::vector<int>& moves, const std::array<ChessField, 64>& board, const MoveInformation& info)
    {

        int from_idx = info.Position.ToInt();
        int king_idx = GetTeamKing(board, info.Team);

        std::set<int> to_erase = std::set<int>();
        
        for (int i = 0; i < moves.size(); i++)
        {
            // If moves[i] is king position, we add it and continue
            if (moves[i] == king_idx)
            {
                to_erase.insert(i);
                continue;
            }

            
            std::array<ChessField, 64> board_copy = board;

            board_copy[moves[i]].Piece = board_copy[from_idx].Piece;
            board_copy[from_idx].Piece = ' ';
            
            bool breakOut = false;
            for (int p = 0; p < board_copy.size(); p++)
            {
                if (breakOut)
                {
                    break;
                }

                if (Helpers::IsChessPiece(board_copy[p].Piece) && !Helpers::IsSameTeam(board_copy[p].Piece, info.Team))
                {
                    std::vector<int> piece_moves = GetMovementPositions(board_copy, p, false);

                    for (int move_idx : piece_moves)
                    {
                        if (move_idx == king_idx)
                        {
                            to_erase.insert(i);
                            breakOut = true;
                            break;
                        }
                    }
                }
            }
        }

        for (int delete_idx : to_erase)
        {
            moves.erase(moves.begin() + delete_idx);
        }
    }

    std::vector<int> GetMovementPositions(const std::array<ChessField, 64>& board, int targetIdx, bool targetCall)
    {
        std::vector<int> moves = std::vector<int>();

        ChessPieceType type = Helpers::GetChessPieceType(board[targetIdx].Piece);
        ChessTeam color = Helpers::GetChessPieceColor(board[targetIdx].Piece);

        Vec2 pos = Vec2(targetIdx);

        auto info = MoveInformation(type, color, pos);

        if (type == ChessPieceType::Pawn)
        {
            GetPawnPositions(moves, board, info);
        }
        else if (type == ChessPieceType::Knight)
        {
            GetKnightPositions(moves, board, info);
        }
        else if (type == ChessPieceType::Rook)
        {
            GetRookPositions(moves, board, info);
        }
        else if (type == ChessPieceType::Bishop)
        {
            GetBishopPositions(moves, board, info);
        }
        else if (type == ChessPieceType::Queen)
        {
            GetQueenPositions(moves, board, info);
        }
        else if (type == ChessPieceType::King)
        {
            GetKingPositions(moves, board, info);
        }

        if (targetCall)
        {
            EliminateCheckPositions(moves, board, info);
        }

        return moves;
    }
}