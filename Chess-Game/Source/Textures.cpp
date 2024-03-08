// Local dependencies
#include "Textures.hpp"

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
    /// Loads an image into the GPU buffer.
    /// </summary>
    /// <param name="filename">The files relative path from the executable</param>
    static void LoadChessTexture(const char* filename)
    {
        static int counter = 0;
        static fs::path base_path = fs::current_path();

        fs::path file_path = base_path / filename;


        Image img = LoadImage(file_path.string().c_str());
        g_Textures[counter++] = LoadTextureFromImage(img);

        UnloadImage(img);
    }

    void LoadChessPieces()
    {
        // King
        LoadChessTexture("Assets/Images/Chess_tile_kd.png");
        LoadChessTexture("Assets/Images/Chess_tile_kl.png");

        // Queen
        LoadChessTexture("Assets/Images/Chess_tile_qd.png");
        LoadChessTexture("Assets/Images/Chess_tile_ql.png");

        // Rook
        LoadChessTexture("Assets/Images/Chess_tile_rd.png");
        LoadChessTexture("Assets/Images/Chess_tile_rl.png");

        // Bishop
        LoadChessTexture("Assets/Images/Chess_tile_bd.png");
        LoadChessTexture("Assets/Images/Chess_tile_bl.png");

        // Knight
        LoadChessTexture("Assets/Images/Chess_tile_nd.png");
        LoadChessTexture("Assets/Images/Chess_tile_nl.png");

        // Pawn
        LoadChessTexture("Assets/Images/Chess_tile_pd.png");
        LoadChessTexture("Assets/Images/Chess_tile_pl.png");
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