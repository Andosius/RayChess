// Local dependencies
#include "GameState.hpp"
#include "Utility.hpp"

// External dependencies


// Standard Library
#include <array>
#include <sstream>

//======================================


GameState::GameState(const std::string& fen)
{
    // Split string
    std::array<std::string, 6> data = std::array<std::string, 6>();

    std::istringstream iss(fen);

    for (int i = 0; i < 6; i++)
    {
        std::string word;
        iss >> word;

        data[i] = word;
    }

    // Parse first part for object information
    std::string pieces = data[0];
    for (size_t i = 0; i < pieces.size(); i++)
    {
        if (pieces[i] == '/')
        {
            continue;
        }

        if (Utility::IsCharNumber(pieces[i]))
        {
            for (int x = 0; x < Utility::ConvertCharToNumber(pieces[i]); x++)
            {
                FenPieceMap.push_back(' ');
            }
        }
        else
        {
            FenPieceMap.push_back(pieces[i]);
        }
    }

    // Player turn
    if (data[1] == "w")
    {
        Turn = ChessColor::White;
    }
    else
    {
        Turn = ChessColor::Black;
    }

    // Castling
    if (data[2].find('K') != std::string::npos)
    {
        WhiteCastlingKing = true;
    }
    if (data[2].find('Q') != std::string::npos)
    {
        WhiteCastlingQueen = true;
    }
    if (data[2].find('k') != std::string::npos)
    {
        BlackCastlingKing = true;
    }
    if (data[2].find('q') != std::string::npos)
    {
        BlackCastlingQueen = true;
    }

    // EnPassant - Target block to eliminate
    if (data[3] != "-")
    {

    }

    // Move Counter
    HalfMoveCounter = std::atoi(data[4].c_str());
    FullMoveEnumerator = std::atoi(data[5].c_str());
}
