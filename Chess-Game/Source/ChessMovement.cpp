#pragma once


// Local dependencies
#include "ChessMovement.hpp"
#include "Vector2.hpp"
#include "ChessHelpers.hpp"

// External dependencies


// Standard Library
#include <string>
#include <set>

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

    static ChessTeam GetEnemyTeam(ChessTeam team)
    {
        if (team == ChessTeam::Black)
        {
            return ChessTeam::White;
        }
        else
        {
            return ChessTeam::Black;
        }
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

        bool canMoveTwo = (info.Team == ChessTeam::Black && info.Position.Y == 1) || (info.Team == ChessTeam::White && info.Position.Y == 6);
        for (int i = 0; i < (canMoveTwo ? 2 : 1); i++)
        {
            Vec2 move = positions_move[i];

            Vec2 test_pos = info.Position + (move * direction);
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

    static void EliminateSelfCheckPositions(std::vector<int>& moves, const std::array<ChessField, 64>& board, const MoveInformation& info)
    {
        std::set<int> remove_moves = std::set<int>();

        // Create a board for every move and simulate it
        for (const int move_location : moves)
        {
            // Copy the board
            std::array<ChessField, 64> boardCopy = board;

            // Replace data - simulate move
            boardCopy[move_location].Piece = boardCopy[info.Position.ToInt()].Piece; // old location is new location
            boardCopy[info.Position.ToInt()].Piece = ' '; // old location is empty

            // Get our own king so we can prevent moves that would expose him to an enemy
            int king_idx = GetTeamKing(board, info.Team);

            // Collect all enemy moves
            std::set<int> enemy_moves = std::set<int>();

            // for every board field (0 - 63), collect moves and add them to enemy_moves
            for (int enemy_idx = 0; enemy_idx < boardCopy.size(); enemy_idx++)
            {
                ChessField& field = boardCopy[enemy_idx];
                if (Helpers::IsChessPiece(field.Piece) && !Helpers::IsSameTeam(field.Piece, info.Team))
                {
                    std::vector<int> tmp_enemy_moves = Move::GetMovementPositions(boardCopy, enemy_idx, false);
                    enemy_moves.insert(std::make_move_iterator(tmp_enemy_moves.begin()), std::make_move_iterator(tmp_enemy_moves.end()));
                }
            }

            // Remove every move where: enemy_pos can be king_idx
            std::set<int>::iterator it = std::find(enemy_moves.begin(), enemy_moves.end(), king_idx);

            // Enemy could attack King - invalidate move
            if (it != enemy_moves.end())
            {
                remove_moves.insert(move_location);
            }
        }

        for (int to_remove : remove_moves)
        {
            std::remove(moves.begin(), moves.end(), to_remove);
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
            EliminateSelfCheckPositions(moves, board, info);
        }

        return moves;
    }
}