#include "gfx/tile.h"
#include <gba_video.h>

void loadTileToMem(const tile_t* tile_p, const u16 tileOffs, u8 baseBlock) {
	for (int j = 0; j < tile_p->tileSize; j++) {
		for (int i = 0; i < 8; i++) {
			PATRAM4(baseBlock, j + tileOffs)[i] = tile_p->tileData[j][i];
		}
	}
}