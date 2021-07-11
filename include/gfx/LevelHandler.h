#pragma once
#include <gba_types.h>
#include <gba_video.h>

#include "level0.h"
#include "Tile.h"

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

typedef struct {
	u16 bgEnable;
	const u16 width;
	const u16 height;
	const u8 numEntities;
	const EntityData_t* entities;
	const u8 numDiffEntities;
	const tile_t** entityTiles;
	const tile_t* levelTileCharacterData;
	const level_t* levelScreenData;
	const u8* tileFlags;
} LevelData_t;

extern const level_t level0;

extern const LevelData_t level0Data;

void scrollLevelU(const level_t* level, u16 x, u16 y);
void scrollLevelD(const level_t* level, u16 x, u16 y);
void scrollLevelL(const level_t* level, u16 x, u16 y);
void scrollLevelR(const level_t* level, u16 x, u16 y);
void refreshLevel(const level_t* level, u16 x, u16 y);

void loadPressStart();
void resetPressStart();
void loadYouWin();
void resetYouWin();
void clearHUD();