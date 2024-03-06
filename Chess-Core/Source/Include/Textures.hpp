#pragma once

// Local dependencies
#include "Definitions.hpp"

// External dependencies
#include <raylib.h>

// Standard Library
#include <array>
#include <filesystem>

//======================================


extern std::array<Texture2D, 12> Textures;


inline void LoadChessTextureToCache(const char* filename)
{
	static int counter = 0;
	static std::filesystem::path base_path = std::filesystem::current_path();

	std::filesystem::path path = base_path / filename;

	Image img = LoadImage(path.string().c_str());
	Textures[counter++] = LoadTextureFromImage(img);

	UnloadImage(img);
}


inline void InitTextures()
{
	// King
	LoadChessTextureToCache("Chess_tile_kd.png");
	LoadChessTextureToCache("Chess_tile_kl.png");
	
	// Queen
	LoadChessTextureToCache("Chess_tile_qd.png");
	LoadChessTextureToCache("Chess_tile_ql.png");

	// Rook
	LoadChessTextureToCache("Chess_tile_rd.png");
	LoadChessTextureToCache("Chess_tile_rl.png");
	
	// Bishop
	LoadChessTextureToCache("Chess_tile_bd.png");
	LoadChessTextureToCache("Chess_tile_bl.png");

	// Knight
	LoadChessTextureToCache("Chess_tile_nd.png");
	LoadChessTextureToCache("Chess_tile_nl.png");

	// Pawn
	LoadChessTextureToCache("Chess_tile_pd.png");
	LoadChessTextureToCache("Chess_tile_pl.png");
}


inline void DeInitTextures()
{
	for (int i = 0; i < 12; i++)
	{
		UnloadTexture(Textures[i]);
	}
}
