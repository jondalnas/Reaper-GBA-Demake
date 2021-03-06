#include "gfx/LevelHandler.h"

const level_t level0 = {level0width, level0height, level0defaultTile, 2, level0ScreenData, level0TileFlag};

const LevelData_t level0Data = {BG0_ON | BG1_ON | BG2_ON, level0width, level0height, 11, level0EntityData, 6, level0EntityTiles, &level0Tiles, &level0, level0TileFlag};

void scrollLevelU(const level_t* level, u16 x, u16 y) {
	short x0 = (x >> 3) - (SCREEN_TILE_WIDTH >> 1) - 1;
	short y0 = (y >> 3) - (SCREEN_TILE_HEIGHT >> 1) - 1;
	
	short yD = y0;
	if (yD < 0)
		yD += VIRTUAL_SCREEN_TILE_SIZE;
	else if (yD >= VIRTUAL_SCREEN_TILE_SIZE)
		yD -= VIRTUAL_SCREEN_TILE_SIZE;
	
	short xD = x0;
	short xS = x0;
	if (xD < 0)
		xD += VIRTUAL_SCREEN_TILE_SIZE;
	for (u8 x = 0; x < SCREEN_TILE_WIDTH+2; x++) {
		if (xD >= VIRTUAL_SCREEN_TILE_SIZE)
			xD -= VIRTUAL_SCREEN_TILE_SIZE;
			
		if (y0 < 0 || xS < 0 || y0 >= level->height || xS >= level->width) {
			((u16*) SCREEN_BASE_BLOCK(8))[xD + yD * VIRTUAL_SCREEN_TILE_SIZE] = level->defaultTile; //BG0
			((u16*) SCREEN_BASE_BLOCK(9))[xD + yD * VIRTUAL_SCREEN_TILE_SIZE] = level->defaultTile; //BG1
		} else {
			((u16*) SCREEN_BASE_BLOCK(8))[xD + yD * VIRTUAL_SCREEN_TILE_SIZE] = level->screenData[0][xS + y0 * level->width]; //BG0
			((u16*) SCREEN_BASE_BLOCK(9))[xD + yD * VIRTUAL_SCREEN_TILE_SIZE] = level->screenData[1][xS + y0 * level->width]; //BG1
		}
		
		xD++;
		xS++;
	}
}

void scrollLevelD(const level_t* level, u16 x, u16 y) {
	short x0 = (x >> 3) - (SCREEN_TILE_WIDTH >> 1) - 1;
	short y1 = (y >> 3) + (SCREEN_TILE_HEIGHT >> 1);
	
	short yD = y1;
	if (yD < 0)
		yD += VIRTUAL_SCREEN_TILE_SIZE;
	else if (yD >= VIRTUAL_SCREEN_TILE_SIZE)
		yD -= VIRTUAL_SCREEN_TILE_SIZE;
	
	short xD = x0;
	short xS = x0;
	if (xD < 0)
		xD += VIRTUAL_SCREEN_TILE_SIZE;
	for (u8 x = 0; x < SCREEN_TILE_WIDTH+2; x++) {
		if (xD >= VIRTUAL_SCREEN_TILE_SIZE)
			xD -= VIRTUAL_SCREEN_TILE_SIZE;
			
		if (y1 < 0 || xS < 0 || y1 >= level->height || xS >= level->width) {
			((u16*) SCREEN_BASE_BLOCK(8))[xD + yD * VIRTUAL_SCREEN_TILE_SIZE] = level->defaultTile; //BG0
			((u16*) SCREEN_BASE_BLOCK(9))[xD + yD * VIRTUAL_SCREEN_TILE_SIZE] = level->defaultTile; //BG1
		} else {
			((u16*) SCREEN_BASE_BLOCK(8))[xD + yD * VIRTUAL_SCREEN_TILE_SIZE] = level->screenData[0][xS + y1 * level->width]; //BG0
			((u16*) SCREEN_BASE_BLOCK(9))[xD + yD * VIRTUAL_SCREEN_TILE_SIZE] = level->screenData[1][xS + y1 * level->width]; //BG1
		}
		
		xD++;
		xS++;
	}
	
}

void scrollLevelL(const level_t* level, u16 x, u16 y) {
	short x0 = (x >> 3) - (SCREEN_TILE_WIDTH >> 1) - 1;
	short y0 = (y >> 3) - (SCREEN_TILE_HEIGHT >> 1) - 1;
	
	short yD = y0;
	short yS = y0;
	if (yD < 0)
		yD += VIRTUAL_SCREEN_TILE_SIZE;
	for (u8 y = 0; y < SCREEN_TILE_HEIGHT+2; y++) {
		if (yD >= VIRTUAL_SCREEN_TILE_SIZE)
			yD -= VIRTUAL_SCREEN_TILE_SIZE;
		
		short xD = x0;
		if (xD < 0)
			xD += VIRTUAL_SCREEN_TILE_SIZE;
		else if (xD >= VIRTUAL_SCREEN_TILE_SIZE)
			xD -= VIRTUAL_SCREEN_TILE_SIZE;
			
		if (yS < 0 || x0 < 0 || yS >= level->height || x0 >= level->width) {
			((u16*) SCREEN_BASE_BLOCK(8))[xD + yD * VIRTUAL_SCREEN_TILE_SIZE] = level->defaultTile; //BG0
			((u16*) SCREEN_BASE_BLOCK(9))[xD + yD * VIRTUAL_SCREEN_TILE_SIZE] = level->defaultTile; //BG1
		} else {
			((u16*) SCREEN_BASE_BLOCK(8))[xD + yD * VIRTUAL_SCREEN_TILE_SIZE] = level->screenData[0][x0 + yS * level->width]; //BG0
			((u16*) SCREEN_BASE_BLOCK(9))[xD + yD * VIRTUAL_SCREEN_TILE_SIZE] = level->screenData[1][x0 + yS * level->width]; //BG1
		}
		
		yD++;
		yS++;
	}
}

void scrollLevelR(const level_t* level, u16 x, u16 y) {
	short x1 = (x >> 3) + (SCREEN_TILE_WIDTH >> 1);
	short y0 = (y >> 3) - (SCREEN_TILE_HEIGHT >> 1) - 1;
	
	short yD = y0;
	short yS = y0;
	if (yD < 0)
		yD += VIRTUAL_SCREEN_TILE_SIZE;
	for (u8 y = 0; y < SCREEN_TILE_HEIGHT+2; y++) {
		if (yD >= VIRTUAL_SCREEN_TILE_SIZE)
			yD -= VIRTUAL_SCREEN_TILE_SIZE;
		
		short xD = x1;
		if (xD < 0)
			xD += VIRTUAL_SCREEN_TILE_SIZE;
		else if (xD >= VIRTUAL_SCREEN_TILE_SIZE)
			xD -= VIRTUAL_SCREEN_TILE_SIZE;
			
		if (yS < 0 || x1 < 0 || yS >= level->height || x1 >= level->width) {
			((u16*) SCREEN_BASE_BLOCK(8))[xD + yD * VIRTUAL_SCREEN_TILE_SIZE] = level->defaultTile; //BG0
			((u16*) SCREEN_BASE_BLOCK(9))[xD + yD * VIRTUAL_SCREEN_TILE_SIZE] = level->defaultTile; //BG1
		} else {
			((u16*) SCREEN_BASE_BLOCK(8))[xD + yD * VIRTUAL_SCREEN_TILE_SIZE] = level->screenData[0][x1 + yS * level->width]; //BG0
			((u16*) SCREEN_BASE_BLOCK(9))[xD + yD * VIRTUAL_SCREEN_TILE_SIZE] = level->screenData[1][x1 + yS * level->width]; //BG1
		}
		
		yD++;
		yS++;
	}
}

void refreshLevel(const level_t* level, u16 x, u16 y) {
	short x0 = (x >> 3) - (SCREEN_TILE_WIDTH >> 1) - 1;
	short y0 = (y >> 3) - (SCREEN_TILE_HEIGHT >> 1) - 1;
	
	short yD = y0;
	short yS = y0;
	if (yD < 0)
		yD += VIRTUAL_SCREEN_TILE_SIZE;
	
	for (u8 y = 0; y < SCREEN_TILE_HEIGHT + 2; y++) {
		if (yD >= VIRTUAL_SCREEN_TILE_SIZE)
			yD -= VIRTUAL_SCREEN_TILE_SIZE;
		
		short xD = x0;
		short xS = x0;
		if (xD < 0)
			xD += VIRTUAL_SCREEN_TILE_SIZE;
		for (u8 x = 0; x < SCREEN_TILE_WIDTH + 2; x++) {
			if (xD >= VIRTUAL_SCREEN_TILE_SIZE)
				xD -= VIRTUAL_SCREEN_TILE_SIZE;
			
			if (yS < 0 || xS < 0 || yS >= level->height || xS >= level->width) {
				((u16*) SCREEN_BASE_BLOCK(8))[xD + yD * VIRTUAL_SCREEN_TILE_SIZE] = level->defaultTile; //BG0
				((u16*) SCREEN_BASE_BLOCK(9))[xD + yD * VIRTUAL_SCREEN_TILE_SIZE] = level->defaultTile; //BG1
			} else {
				((u16*) SCREEN_BASE_BLOCK(8))[xD + yD * VIRTUAL_SCREEN_TILE_SIZE] = level->screenData[0][xS + yS * level->width]; //BG0
				((u16*) SCREEN_BASE_BLOCK(9))[xD + yD * VIRTUAL_SCREEN_TILE_SIZE] = level->screenData[1][xS + yS * level->width]; //BG1
			}
			
			xD++;
			xS++;
		}
		
		yD++;
		yS++;
	}
}

void loadPressStart() {
	for (u8 x = 0; x < 8; x++) {
		((u16*) SCREEN_BASE_BLOCK(10))[(x + (SCREEN_TILE_WIDTH >> 1) - 3) + ((SCREEN_TILE_HEIGHT >> 1) - 2) * VIRTUAL_SCREEN_TILE_SIZE] = x + 256;
	}
}

void removePressStart() {
	for (u8 x = 0; x < 8; x++) {
		((u16*) SCREEN_BASE_BLOCK(10))[(x + (SCREEN_TILE_WIDTH >> 1) - 3) + ((SCREEN_TILE_HEIGHT >> 1) - 2) * VIRTUAL_SCREEN_TILE_SIZE] = 16;
	}
}

void loadYouWin() {
	for (u8 x = 0; x < 5; x++) {
		((u16*) SCREEN_BASE_BLOCK(10))[(x + (SCREEN_TILE_WIDTH >> 1) - 2) + ((SCREEN_TILE_HEIGHT >> 1) - 4) * VIRTUAL_SCREEN_TILE_SIZE] = x + 256 + 8;
	}
}

void removeYouWin() {
	for (u8 x = 0; x < 5; x++) {
		((u16*) SCREEN_BASE_BLOCK(10))[(x + (SCREEN_TILE_WIDTH >> 1) - 2) + ((SCREEN_TILE_HEIGHT >> 1) - 4) * VIRTUAL_SCREEN_TILE_SIZE] = 16;
	}
}

void clearHUD() {
	for (u8 y = 0; y < SCREEN_TILE_HEIGHT; y++) {
		for (u8 x = 0; x < SCREEN_TILE_WIDTH; x++) {
			((u16*) SCREEN_BASE_BLOCK(10))[x + y * VIRTUAL_SCREEN_TILE_SIZE] = 16;
		}
	}
}