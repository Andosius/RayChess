#pragma once


// Local dependencies


// External dependencies
#include <raylib.h>

// Standard Library
#include <array>

//======================================


extern std::array<Texture, 12> g_Textures;


namespace Textures
{
    /// <summary>
    /// Loads hard-coded images into GPU buffer which are exposed to the g_Textures array.
    /// </summary>
    void LoadChessPieces();

    /// <summary>
    /// Unloads all chess piece textures from GPU buffer.
    /// </summary>
    void UnloadChessPieces();

    /// <summary>
    /// Returns the chess piece texture index
    /// </summary>
    /// <param name="piece">char that represents the chess piece</param>
    /// <returns>int Chess piece index inside g_Textures</returns>
    int GetChessPieceTextureIndex(char piece);
}

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
