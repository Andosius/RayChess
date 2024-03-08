// Local dependencies
#include "Application.hpp"
#include "Textures.hpp"
#include "Chess.hpp"

// External dependencies
#include <raylib.h>

// Standard Library
#include <iostream>

//======================================


namespace Application
{
    void Run()
    {
        Chess game = Chess();
        Textures::LoadChessPieces();

        while (!WindowShouldClose())
        {
            game.DrawChessBoard();
        }

        Textures::UnloadChessPieces();
    }
}