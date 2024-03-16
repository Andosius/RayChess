// Local dependencies
#include "Textures.hpp"

#include "Images/BlackKing.hpp"
#include "Images/WhiteKing.hpp"

#include "Images/BlackQueen.hpp"
#include "Images/WhiteQueen.hpp"

#include "Images/BlackRook.hpp"
#include "Images/WhiteRook.hpp"

#include "Images/BlackBishop.hpp"
#include "Images/WhiteBishop.hpp"

#include "Images/BlackKnight.hpp"
#include "Images/WhiteKnight.hpp"

#include "Images/BlackPawn.hpp"
#include "Images/WhitePawn.hpp"

// External dependencies


// Standard Library
#include <filesystem>

//======================================

namespace fs = std::filesystem;


std::array<Texture, 12> g_Textures = std::array<Texture, 12>();
std::array<Image, 12> g_Images = std::array<Image, 12>();


namespace Textures
{
    /// <summary>
    /// Loads an images into the GPU buffer by reading a hex dump.
    /// </summary>
    /// <param name="data">The hex dump data</param>
    /// <param name="size">The array size</param>
    static void LoadChessTextureFromMemory(const unsigned char* data, int size)
    {
        static int counter = 0;

        Image img = LoadImageFromMemory(".png", data, size);
        g_Textures[counter++] = LoadTextureFromImage(img);

        UnloadImage(img);
    }

    void LoadChessPieces()
    {
        // King
        LoadChessTextureFromMemory(BlackKingData, 4562);
        LoadChessTextureFromMemory(WhiteKingData, 5083);

        // Queen
        LoadChessTextureFromMemory(BlackQueenData, 4176);
        LoadChessTextureFromMemory(WhiteQueenData, 7039);

        // Rook
        LoadChessTextureFromMemory(BlackRookData, 2465);
        LoadChessTextureFromMemory(WhiteRookData, 2817);

        // Bishop
        LoadChessTextureFromMemory(BlackBishopData, 3475);
        LoadChessTextureFromMemory(WhiteBishopData, 4370);

        // Knight
        LoadChessTextureFromMemory(BlackKnightData, 4203);
        LoadChessTextureFromMemory(WhiteKnightData, 4416);

        // Pawn
        LoadChessTextureFromMemory(BlackPawnData, 2457);
        LoadChessTextureFromMemory(WhitePawnData, 3323);
    }

    void UnloadChessPieces()
    {
        // This should never fail, we use exactly 12 images!
        for (int i = 0; i < 12; i++)
        {
            UnloadTexture(g_Textures[i]);
        }
    }

    int GetChessPieceTextureIndex(char piece)
    {
        int idx = -1;

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
}