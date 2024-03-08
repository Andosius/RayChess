#pragma once


// Local dependencies


// External dependencies


// Standard Library
#include <string>

//======================================


constexpr int FIELD_WIDTH = 100;
constexpr int FIELD_HEIGHT = 100;
constexpr int PIECE_SIZE = 80;
constexpr int PIECE_OFFSET = (FIELD_WIDTH - PIECE_SIZE) / 2;

const std::string DEFAULT_FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
