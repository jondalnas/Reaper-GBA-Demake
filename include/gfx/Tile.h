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
extern const tile_t playerTiles;
extern const tile_t scytheTiles;
extern const tile_t swingTiles;
extern const tile_t cursorTiles;
extern const tile_t teleportTiles;
extern const tile_t brawlerTiles;

extern const tile_t* level0EntityTiles[6];

//BG tiles
extern const tile_t level0Tiles;
extern const tile_t textTiles[];

void loadTileToMem(const tile_t* tile_p, const u16 tileOffs, u8 baseBlock);
void clearTile(const u16 tileOffs, u8 baseBlock);