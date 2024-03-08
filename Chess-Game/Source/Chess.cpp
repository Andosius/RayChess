// Local dependencies
#include "Chess.hpp"
#include "Constants.hpp"
#include "Textures.hpp"

// External dependencies
#include <raylib.h>

// Standard Library


//======================================

#define RENDER_THROUGH_TEXTURE

Chess::Chess()
    : m_GameState(DEFAULT_FEN)
{
    InitWindow(FIELD_WIDTH * 8, FIELD_WIDTH * 8, "Chess Board");
    SetTargetFPS(20);

    Textures::LoadChessPieces();

    {
        m_BoardTexture = Texture2D{};

        m_ColorBlack = BLUE;
        m_ColorWhite = WHITE;
        m_ColorSelected = GREEN;
        m_ColorMove = RED;
        m_ColorLastMove = YELLOW;
    }

    GameStateToBoard();
    GenerateBoardTexture();
}

Chess::~Chess()
{
    UnloadTexture(m_BoardTexture);
    Textures::UnloadChessPieces();
}

void Chess::GameStateToBoard()
{
    bool drawColor = true;
    for (int i = 0; i < 64; i++)
    {
        int column = i % 8;
        int row = i / 8;

        // Flip for next row so they never start with the same color
        if (column == 0 && row != 0)
        {
            drawColor = !drawColor;
        }

        m_Board[i] = ChessField(drawColor ? m_ColorBlack : m_ColorWhite, m_GameState.FenPieceMap[i]);
        drawColor = !drawColor;
    }
}

void Chess::GenerateBoardTexture()
{
    int height = FIELD_WIDTH * 8;
    int width = FIELD_WIDTH * 8;

    int buffer_size = height * width * sizeof(Color);

    Color* pixels = (Color*)RL_MALLOC(buffer_size);

    if (pixels != nullptr)
    {
        for (int i = 0; i < m_Board.size(); i++)
        {
            int column = i % 8;
            int row = i / 8;

            // Draw fields
            for (int y = row * FIELD_HEIGHT; y < (row + 1) * FIELD_HEIGHT; y++)
            {
                for (int x = column * FIELD_WIDTH; x < (column + 1) * FIELD_WIDTH; x++)
                {
                    pixels[y * width + x] = m_Board[i].FieldColor;
                }
            }
        }

        Image img = {};
        img.data = pixels;
        img.height = height;
        img.width = width;
        img.mipmaps = 1;
        img.format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8;

        // Clear last texture
        UnloadTexture(m_BoardTexture);

        m_BoardTexture = LoadTextureFromImage(img);
        UnloadImage(img);
    }
}

void Chess::DrawChessBoard()
{
    BeginDrawing();

    {
        DrawTexture(m_BoardTexture, 0, 0, WHITE);

        for (int i = 0; i < m_Board.size(); i++)
        {
            if (m_Board[i].Piece != ' ')
            {
                int column = i % 8;
                int row = i / 8;
                
                DrawTexture(g_Textures[Textures::GetChessPieceTextureIndex(m_Board[i].Piece)], column * FIELD_WIDTH + PIECE_OFFSET, row * FIELD_HEIGHT + PIECE_OFFSET, WHITE);
            }
        }
    }

    EndDrawing();
}
