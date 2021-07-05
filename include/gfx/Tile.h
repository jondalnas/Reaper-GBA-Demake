#pragma once

#include <gba_types.h>
#include "player.h"
#include "level0.h"
#include "brawler.h"

#define OBJ_BLOCK 4

typedef struct {
	const u8 tileSize;
	const u32 (*tileData)[8];
} tile_t;

//OBJ tiles
const tile_t playerTiles = {playerTileSize,  playerTileData};
const tile_t scytheTiles = {scytheTileSize,  scytheTileData};
const tile_t swingTiles = {swingTileSize,  swingTileData};
const tile_t cursorTiles = {cursorTileSize,  cursorTileData};
const tile_t brawlerTiles = {brawlerTileSize,  brawlerTileData};

//BG tiles
const tile_t level0Tiles = {7, level0TileData};

void loadTileToMem(const tile_t* tile_p, const u16 tileOffs, u8 baseBlock);