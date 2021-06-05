#pragma once
#include <gba_types.h>
#include <gba_video.h>

#include "level0.h"

#define SCREEN_TILE_WIDTH 30
#define SCREEN_TILE_HEIGHT 20

#define VIRTUAL_SCREEN_TILE_SIZE 32

typedef struct {
	const u16 width;
	const u16 height;
	const u16 defaultTile;
	const u8 backgrounds;
	const u16** screenData;
	const u8* tileFlags;
} level_t;

const level_t level0 = {level0width, level0height, level0defaultTile, 2, level0ScreenData, level0TileFlag};

void scrollLevelU(const level_t* level, u16 x, u16 y);
void scrollLevelD(const level_t* level, u16 x, u16 y);
void scrollLevelL(const level_t* level, u16 x, u16 y);
void scrollLevelR(const level_t* level, u16 x, u16 y);