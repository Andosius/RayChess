// Local dependencies
#include "Application.hpp"
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

        while (!WindowShouldClose())
        {
            game.DrawChessBoard();
        }
    }
}