// Local dependencies
#include "Chess.hpp"
#include "Constants.hpp"
#include "Textures.hpp"
#include "ChessMovement.hpp"
#include "ChessHelpers.hpp"

// External dependencies
#include <raylib.h>

// Standard Library
#include <algorithm>

//======================================

#define RENDER_THROUGH_TEXTURE

Chess::Chess()
    : State(DEFAULT_FEN)
{
    InitWindow(FIELD_WIDTH * 8, FIELD_WIDTH * 8, "Chess Board");
    SetTargetFPS(20);

    Textures::LoadChessPieces();

    {
        m_SelectedPositions = std::vector<int>();
        m_BoardTexture = Texture2D{};

        m_ColorBlack = BLUE;
        m_ColorWhite = WHITE;
        m_ColorSelected = GREEN;
        m_ColorMove = RED;
        m_ColorLastMove = YELLOW;
        m_ColorMarked = PURPLE;

        m_TargetPiece = INVALID_TARGET_PIECE;
    }

    GameStateToBoard();
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

        Board[i] = ChessField(drawColor ? m_ColorBlack : m_ColorWhite, State.FenPieceMap[i]);
        drawColor = !drawColor;
    }

    if (m_TargetPiece != INVALID_TARGET_PIECE)
    {
        Board[m_TargetPiece].FieldColor = m_ColorSelected;
    }
    for (int i = 0; i < m_SelectedPositions.size(); i++)
    {
        Board[m_SelectedPositions[i]].FieldColor = m_ColorMarked;
    }
    for (int i = 0; i < m_PossibleMoves.size(); i++)
    {
        Board[m_PossibleMoves[i]].FieldColor = m_ColorMove;
    }

    GenerateBoardTexture();
}

void Chess::GenerateBoardTexture()
{
    int height = FIELD_WIDTH * 8;
    int width = FIELD_WIDTH * 8;

    int buffer_size = height * width * sizeof(Color);

    Color* pixels = (Color*)RL_MALLOC(buffer_size);

    if (pixels != nullptr)
    {
        for (int i = 0; i < Board.size(); i++)
        {
            int column = i % 8;
            int row = i / 8;

            // Draw fields
            for (int y = row * FIELD_HEIGHT; y < (row + 1) * FIELD_HEIGHT; y++)
            {
                for (int x = column * FIELD_WIDTH; x < (column + 1) * FIELD_WIDTH; x++)
                {
                    pixels[y * width + x] = Board[i].FieldColor;
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

        for (int i = 0; i < Board.size(); i++)
        {
            if (Helpers::IsChessPiece(Board[i].Piece))
            {
                int column = i % 8;
                int row = i / 8;
                
                DrawTexture(g_Textures[Textures::GetChessPieceTextureIndex(Board[i].Piece)], column * FIELD_WIDTH + PIECE_OFFSET, row * FIELD_HEIGHT + PIECE_OFFSET, WHITE);
            }
        }
    }

    EndDrawing();
}

void Chess::HandleInput()
{
    Vector2 pos = GetMousePosition();
    Vec2 relative_pos = Vec2((int)pos.x / FIELD_WIDTH, (int)pos.y / FIELD_HEIGHT);

    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    {

        if (relative_pos.IsValidPosition())
        {
            if (Helpers::IsChessPiece(Board[relative_pos.ToInt()].Piece))
            {
                int target_idx = relative_pos.ToInt();

                if (target_idx != m_TargetPiece)
                {
                    m_TargetPiece = relative_pos.ToInt();
                    m_PossibleMoves = Move::GetMovementPositions(Board, relative_pos.ToInt(), true);

                    GameStateToBoard();
                }
            }
            else
            {
                if (m_TargetPiece != INVALID_TARGET_PIECE)
                {
                    m_TargetPiece = INVALID_TARGET_PIECE;
                    m_PossibleMoves.clear();

                    GameStateToBoard();
                }
            }
        }
        else
        {
            m_TargetPiece = INVALID_TARGET_PIECE;
            m_PossibleMoves.clear();
        }
    }
    else if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT))
    {
        m_TargetPiece = INVALID_TARGET_PIECE;
        if (relative_pos.IsValidPosition())
        {
            std::vector<int>::iterator it = std::find(m_SelectedPositions.begin(), m_SelectedPositions.end(), relative_pos.ToInt());

            if (it == m_SelectedPositions.end())
            {
                m_SelectedPositions.push_back(relative_pos.ToInt());
            }
            else
            {
                m_SelectedPositions.erase(it);
            }
            GameStateToBoard();
        }
    }
}
