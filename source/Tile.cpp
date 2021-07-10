#include "gfx/Tile.h"
#include <gba_video.h>

#include "gfx/text.h"

const tile_t playerTiles = {playerTileSize,  playerTileData};
const tile_t scytheTiles = {scytheTileSize,  scytheTileData};
const tile_t swingTiles = {swingTileSize,  swingTileData};
const tile_t cursorTiles = {cursorTileSize,  cursorTileData};
const tile_t teleportTiles = {teleportTileSize,  teleportTileData};
const tile_t brawlerTiles = {brawlerTileSize,  brawlerTileData};

const tile_t* level0EntityTiles[6] = {&playerTiles, &scytheTiles, &swingTiles, &cursorTiles, &teleportTiles, &brawlerTiles};

const tile_t level0Tiles = {7, level0TileData};

const tile_t textTiles = {pressStartTileSize, pressStartTileData};

void loadTileToMem(const tile_t* tile_p, const u16 tileOffs, u8 baseBlock) {
	for (int j = 0; j < tile_p->tileSize; j++) {
		for (int i = 0; i < 8; i++) {
			PATRAM4(baseBlock, j + tileOffs)[i] = tile_p->tileData[j][i];
		}
	}
}

void clearTile(const u16 tileOffs, u8 baseBlock) {
	for (int i = 0; i < 8; i++) {
		PATRAM4(baseBlock, tileOffs)[i] = 0;
	}
}