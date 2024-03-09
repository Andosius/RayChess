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
        Turn = ChessTeam::White;
    }
    else
    {
        Turn = ChessTeam::Black;
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
        char alpha = data[3][0];
        char num = data[3][1];

        Vec2 data = Vec2(static_cast<int>(alpha - CHAR_LOWER_START), static_cast<int>(num - CHAR_NUM_START));
    }

    // Move Counter
    HalfMoveCounter = std::atoi(data[4].c_str());
    FullMoveEnumerator = std::atoi(data[5].c_str());
}

std::string GameState::Export()
{
    std::string result = "";

    // Part 1 - Locations
    int empty_counter = 0;
    for (int i = 0; i < FenPieceMap.size(); i++)
    {
        if (i % 8 == 0 && i != 0 && i != FenPieceMap.size() - 1)
        {
            if (empty_counter != 0)
            {
                result += std::to_string(empty_counter);
                empty_counter = 0;
            }

            result += "/";
        }

        if (FenPieceMap[i] != ' ')
        {
            result += FenPieceMap[i];
        }
        else
        {
            empty_counter++;
        }
    }
    result += " ";

    // Part 2 - Turn
    if (Turn == ChessTeam::White)
    {
        result += "w";
    }
    else
    {
        result += "b";
    }
    result += " ";

    // Part 3 - Castling
    if (WhiteCastlingKing)
    {
        result += "K";
    }
    if (WhiteCastlingQueen)
    {
        result += "Q";
    }
    if (BlackCastlingKing)
    {
        result += "k";
    }
    if (BlackCastlingQueen)
    {
        result += "q";
    }
    result += " ";

    // Part 4 - En Passant
    if (EnPassant.IsValidPosition())
    {
        char enpassant[2] = {};
        enpassant[0] = static_cast<char>(EnPassant.X + CHAR_LOWER_START);
        enpassant[1] = static_cast<char>(EnPassant.Y + CHAR_NUM_START);

        result += enpassant;
    }
    else
    {
        result += "-";
    }
    result += " ";
    
    // Part 5 - Half move counter
    result += std::to_string(HalfMoveCounter);
    result += " ";

    // Part 6 - Full move enumerator
    result += std::to_string(FullMoveEnumerator);

    return result;
}
