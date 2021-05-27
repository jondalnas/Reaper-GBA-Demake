#pragma once

#include <gba_types.h>
#include "player.h"
#include "level0.h"

#define OBJ_BLOCK 4

typedef struct {
	const u8 tileSize;
	const u32 (*tileData)[8];
} tile_t;

//OBJ tiles
const tile_t playerTiles = {playerTileSize, playerTileData};

//BG tiles
const tile_t level0Tiles = {1, &floorTileData};

void loadTileToMem(const tile_t* tile_p, const u16 tileOffs, u8 baseBlock);