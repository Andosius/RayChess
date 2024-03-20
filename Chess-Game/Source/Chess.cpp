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
        for (size_t i = 0; i < 64; i++)
        {
            Board[i] = ChessField();
        }

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

        Board[i].AddSpecialColor(drawColor ? m_ColorBlack : m_ColorWhite);
        Board[i].Piece = State.FenPieceMap[i];

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

#ifdef DEBUG
            // Write locations
            char data[6] = {
                '(', column + 48, '|', row + 48, ')', '\0'
            };

            DrawText(data, column * FIELD_WIDTH, row * FIELD_HEIGHT, 14, BLACK);
#endif
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

void Chess::OnPlayerLeftClickBoard(const Vec2& position, bool isChessPiece)
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

void Chess::OnPlayerReleaseLeftClickBoard(const Vec2& position, bool isPossibleMove)
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

void Chess::OnPlayerRightClickBoard(const Vec2& position)
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

void Chess::OnMoveHappened(const Vec2& from, const Vec2& to)
{
    int new_pos_idx = to.ToInt();
    UpdateGameInformation(from, to);

    if (Helpers::GetChessPieceType(Board[to.ToInt()].Piece) == ChessPieceType::Pawn)
    {
        HandleSpecialPawnInteractions(from, to);
    }

    // TODO:
    // 
    // Castling
    // HandleSpecialKingInteractions(from, to);
    // Game end => total moves = 0, king_idx inside moves via it
    //
    // Save FEN after everything is proccessed
    // FEN can be loaded by calling State = GameState(std::string containing FEN)
    // Saved by State.Export();
    
#ifdef DEBUG
    printf("Moved piece from (%d|%d) to (%d|%d)!\n", from.X, from.Y, to.X, to.Y);
#endif
}

void Chess::UpdateGameInformation(const Vec2& from, const Vec2& to)
{
    int new_pos_idx = to.ToInt();

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
}

void Chess::HandleSpecialPawnInteractions(const Vec2& from, const Vec2& to)
{
    if (State.EnPassant.IsValidPosition())
    {
        // Second check just in case we get some random behavior
        if (State.EnPassant == to && to.X != from.X)
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
        ChessTeam team = Helpers::GetChessPieceColor(Board[m_TargetPiece].Piece);

        // Get the difference between to and from and take the half of Y as X must be 0!
        Vec2 delta = (to - from);
        delta.Y /= 2;

        // Set EnPassant to our from-position and add delta to it.
        State.EnPassant = from + delta;
        State.EnPassantTarget = to;
    }

    // TODO:
    // Possible promotion!!

#ifdef DEBUG
    printf("EnPassant is now at (%d|%d)!\n", State.EnPassant.X, State.EnPassant.Y);
#endif
}