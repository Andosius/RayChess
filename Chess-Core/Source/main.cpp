// Local dependencies
#include "Board.hpp"

// External dependencies
#include <raylib.h>

// Standard Library
#include "Vector2.hpp"

//======================================

int main(void)
{
    Board board = Board();

    SetTargetFPS(20);

    while (!WindowShouldClose())
    {

        BeginDrawing();

        {
            board.SetBoardColors();
            board.HandleEvents();

            board.DrawBoard();
            board.DrawPieces();
        }

        EndDrawing();
    }

    return 0;
}