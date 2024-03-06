// Local dependencies
#include "Board.hpp"
#include "Textures.hpp"
#include "Utility.hpp"

// External dependencies


// Standard Library
#include <array>
#include <sstream>

//======================================

// Queen => 27 possible fields from the middle
#define MAX_MOVES 27
#define MAX_CHESS_PIECES 32


std::array<Texture2D, 12> Textures = std::array<Texture2D, 12>();


Board::Board()
{
    m_GameState = {};

    m_Moves = std::vector<Vec2>();
    m_Moves.reserve(MAX_MOVES);

    m_Fen = std::vector<std::string>();

    m_Fen.push_back(DEFAULT_FEN);
    m_FenIndex = 0;

    for (int i = 0; i < 8; i++)
    {
        for (int x = 0; x < 8; x++)
        {
            BoardColors[i][x] = WHITE;
        }
    }

    m_SelectedPos = Vec2(-1, -1);

    InitWindow(FIELD_WIDTH * 8, FIELD_WIDTH * 8, "Chess Board");
    InitTextures();

    ConfigureByFen(m_FenIndex);
}

Board::~Board()
{
    CloseWindow();
    DeInitTextures();
}

void Board::DrawBoard()
{
    for (int row = 0; row < 8; row++)
    {
        for (int column = 0; column < 8; column++)
        {
            DrawRectangle(column * FIELD_WIDTH, row * FIELD_WIDTH, FIELD_WIDTH, FIELD_WIDTH, BoardColors[column][row]);
        
            // Write numbers 1-8
            if (column == 0)
            {
                char data[2] = { (char)(56 - row), '\0' };
                DrawText(data, 5, row * FIELD_WIDTH + 5, 20, BLACK);
            }
        
            // Write characters a-h
            if (row == 7)
            {
                char data[2] = { (char)(105 - 8 + column), '\0' };
                DrawText(data, column * FIELD_WIDTH + 85, row * FIELD_WIDTH + 5, 20, BLACK);
            }
        }
    }
}

void Board::DrawPieces()
{
    std::string data = m_GameState.FenPieceMap;

    for (int i = 0; i < data.size(); i++)
    {
        int column = i % 8;
        int row = i / 8;

        if (data[i] != ' ')
        {
            DrawTexture(Textures[Utility::GetTextureIndex(data[i])], column * FIELD_WIDTH + PIECE_OFFSET, row * FIELD_WIDTH + PIECE_OFFSET, WHITE);
        }
    }
}

void Board::HandleEvents()
{
    Vector2 pos = GetMousePosition();
    Vec2 relative_pos{ (int)pos.x / FIELD_WIDTH, (int)pos.y / FIELD_WIDTH };

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        m_SelectedPos = relative_pos;
    }

    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    {
        if (m_SelectedPos != relative_pos)
        {
            printf("Insert movement logic here!\n");
        }
    }
}

void Board::SetBoardColors()
{
    bool drawColor = true;
    for (int i = 0; i < 64; i++)
    {
        int column = i % 8;
        int row = i / 8;

        if (column == 0 && row != 0)
        {
            drawColor = !drawColor;
        }

        BoardColors[column][row] = (drawColor ? COLORFUL_PIECE_COLOR : WHITE_PIECE_COLOR);
        drawColor = !drawColor;
    }
    
    if (m_SelectedPos.IsValidPosition())
    {
        BoardColors[m_SelectedPos.X][m_SelectedPos.Y] = SELECTED_PIECE_COLOR;
    }

    for (const auto& move : m_Moves)
    {
        if (move.IsValidPosition())
        {
            BoardColors[move.X][move.Y] = POSSIBLE_MOVE_COLOR;
        }
    }
}

void Board::ConfigureByFen(const size_t index)
{
    m_GameState = {};

    // Split string
    std::array<std::string, 6> data = std::array<std::string, 6>();

    std::string fen = m_Fen.at(index);
    std::istringstream iss(fen);

    for (int i = 0; i < 6; i++)
    {
        std::string word;
        iss >> word;

        data[i] = word;
    }

    // Parse first part for object information
    std::string pieces = data[0];
    for (size_t i = 0; i < pieces.size(); i++)
    {
        if (pieces[i] == '/')
        {
            continue;
        }

        if (Utility::IsNumber(pieces[i]))
        {
            for (int x = 0; x < Utility::CharToNumber(pieces[i]); x++)
            {
                m_GameState.FenPieceMap.push_back(' ');
            }
        }
        else
        {
            m_GameState.FenPieceMap.push_back(pieces[i]);
        }
    }

    // Player turn
    if (data[1] == "w")
    {
        m_GameState.Turn = ChessColor::White;
    }
    else
    {
        m_GameState.Turn = ChessColor::Black;
    }

    // Castling
    if (data[2].find('K') != std::string::npos)
    {
        m_GameState.WhiteCastlingKing = true;
    }
    if (data[2].find('Q') != std::string::npos)
    {
        m_GameState.WhiteCastlingQueen = true;
    }
    if (data[2].find('k') != std::string::npos)
    {
        m_GameState.BlackCastlingKing = true;
    }
    if (data[2].find('q') != std::string::npos)
    {
        m_GameState.BlackCastlingQueen = true;
    }

    // EnPassant - Target block to eliminate
    if (data[3] != "-")
    {

    }

    // Move Counter
    m_GameState.HalfMoveCounter = std::atoi(data[4].c_str());
    m_GameState.FullMoveEnumerator = std::atoi(data[5].c_str());
}

