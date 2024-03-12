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


Chess* g_Chess;


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

        m_ColorBlack.a = 180;
        m_ColorWhite.a = 180;
        m_ColorSelected.a = 180;
        m_ColorMove.a = 180;
        m_ColorLastMove.a = 180;
        m_ColorMarked.a = 180;

        m_TargetPiece = INVALID_TARGET_PIECE;

        m_IsMoving = false;
    }

    g_Chess = this;

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
    for (int i = 0; i < Board.size(); i++)
    {
        Board[i].ResetSpecialColor();

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

    // Apply covers to special colors set
    if (m_TargetPiece != INVALID_TARGET_PIECE)
    {
        Board[m_TargetPiece].AddSpecialColor(m_ColorSelected);
    }
    for (int i = 0; i < m_SelectedPositions.size(); i++)
    {
        Board[m_SelectedPositions[i]].AddSpecialColor(m_ColorMarked);
    }
    for (int i = 0; i < m_PossibleMoves.size(); i++)
    {
        Board[m_PossibleMoves[i]].AddSpecialColor(m_ColorMove);
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

        // Unload image frees the pixels buffer!
        m_BoardTexture = LoadTextureFromImage(img);
        UnloadImage(img);
    }
}

void Chess::DrawChessBoard()
{
    BeginDrawing();

    {
        ClearBackground(WHITE);
        DrawTexture(m_BoardTexture, 0, 0, WHITE);

        for (int i = 0; i < Board.size(); i++)
        {
            int column = i % 8;
            int row = i / 8;

            // Overlay colors
            if (Board[i].ColorCount > 0)
            {
                DrawRectangle(column * FIELD_WIDTH, row * FIELD_HEIGHT, FIELD_WIDTH, FIELD_HEIGHT, Board[i].GetSpecialColor());
            }

            // Chess pieces
            if (Helpers::IsChessPiece(Board[i].Piece))
            {
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

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (relative_pos.IsValidPosition() && Helpers::IsChessPiece(Board[relative_pos.ToInt()].Piece))
        {
            OnPlayerLeftClickBoard(relative_pos, true);
            m_IsMoving = true;
        }
        else
        {
            OnPlayerLeftClickBoard(relative_pos, false);
        }
    }
    else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    {
        std::vector<int>::iterator it = std::find(m_PossibleMoves.begin(), m_PossibleMoves.end(), relative_pos.ToInt());

        if (m_IsMoving && it != m_PossibleMoves.end())
        {
            OnPlayerReleaseLeftClickBoard(relative_pos, true);
        }
        else
        {
            OnPlayerReleaseLeftClickBoard(relative_pos, false);
        }
    }
    else if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT))
    {
        if (relative_pos.IsValidPosition())
        {
            OnPlayerRightClickBoard(relative_pos);
        }
    }
}

void Chess::OnPlayerLeftClickBoard(Vec2 position, bool isChessPiece)
{
    if (isChessPiece)
    {
        int target_idx = position.ToInt();

        if (target_idx != m_TargetPiece)
        {
            m_TargetPiece = position.ToInt();
            m_PossibleMoves = Move::GetMovementPositions(Board, position.ToInt(), true);

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

void Chess::OnPlayerReleaseLeftClickBoard(Vec2 position, bool isPossibleMove)
{
    int new_pos_idx = position.ToInt();

    if (isPossibleMove)
    {
        if (m_IsMoving && new_pos_idx != m_TargetPiece && m_TargetPiece != INVALID_TARGET_PIECE && Helpers::IsSameTeam(Board[m_TargetPiece].Piece, State.Turn))
        {
            OnMoveHappened(Vec2(m_TargetPiece), Vec2(position));
            GameStateToBoard();
        }
    }
    else
    {
        m_IsMoving = false;
    }
}

void Chess::OnPlayerRightClickBoard(Vec2 position)
{
    std::vector<int>::iterator it = std::find(m_SelectedPositions.begin(), m_SelectedPositions.end(), position.ToInt());
    if (it == m_SelectedPositions.end())
    {
        m_SelectedPositions.push_back(position.ToInt());
    }
    else
    {
        m_SelectedPositions.erase(it);
    }

    GameStateToBoard();
}

void Chess::OnMoveHappened(Vec2 from, Vec2 to)
{
    int new_pos_idx = to.ToInt();
    ChessTeam team = Helpers::GetChessPieceColor(Board[m_TargetPiece].Piece);

    // Update Board and FEN data
    Board[new_pos_idx].Piece = Board[m_TargetPiece].Piece;
    State.FenPieceMap[new_pos_idx] = Board[m_TargetPiece].Piece;

    Board[m_TargetPiece].Piece = ' ';
    State.FenPieceMap[m_TargetPiece] = ' ';

    if (State.Turn == ChessTeam::White)
    {
        State.Turn = ChessTeam::Black;
    }
    else
    {
        State.Turn = ChessTeam::White;
    }


    if (Helpers::GetChessPieceType(Board[new_pos_idx].Piece) == ChessPieceType::Pawn)
    {
        if (State.EnPassant.IsValidPosition())
        {
            if (State.EnPassant == to)
            {
                int enpassant_idx = State.EnPassantTarget.ToInt();

                Board[enpassant_idx].Piece = ' ';
                State.FenPieceMap[enpassant_idx] = ' ';
            }

            State.EnPassant = Vec2(-1, -1);
            State.EnPassantTarget = Vec2(-1, -1);
        }

        // Add EnPassant behind pawn
        if (Vec2::GetDistance(from, to) == 2)
        {
            // Negate Y because we want to go 1 backwards
            Vec2 direction = (team == ChessTeam::Black) ? Vec2(1, 1) : Vec2(1, -1);
            direction.Y *= -1;

            // Set EnPassant Vec2 for now, implement it later
            State.EnPassant = to + (Vec2(0, 1) * direction);
            State.EnPassantTarget = to;
        }

        // To Do: Pawn Promotion!!!
    }

    
#ifdef DEBUG
    printf("Moved piece from (%d|%d) to (%d|%d)!\n", from.X, from.Y, to.X, to.Y);
#endif
}
