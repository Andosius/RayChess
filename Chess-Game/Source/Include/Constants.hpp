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

constexpr int CHAR_NUM_START = 48;
constexpr int CHAR_NUM_END = 57;

constexpr int CHAR_TO_NUM_DIFF = 48;

constexpr int CHAR_UPPER_START = 65;
constexpr int CHAR_UPPER_END = 90;

constexpr int CHAR_LOWER_START = 97;
constexpr int CHAR_LOWER_END = 122;

constexpr int INVALID_TARGET_PIECE = -1;
