#include "Level.h"
#include "Player.h"

#include <gba_video.h>
#include <gba_sprites.h>
#include <stdlib.h>

void Level::update() {
	for (int i = 0; i < numEnt; i++) {
		entities[i]->update();
	}
	
	x = player->x;
	y = player->y;
	
	BG_OFFSET[0].x = x - (SCREEN_WIDTH >> 1) - 4;
	BG_OFFSET[0].y = y - (SCREEN_HEIGHT >> 1) - 4;
	BG_OFFSET[1].x = x - (SCREEN_WIDTH >> 1);
	BG_OFFSET[1].y = y - (SCREEN_HEIGHT >> 1);
	BG_OFFSET[2].x = x - (SCREEN_WIDTH >> 1);
	BG_OFFSET[2].y = y - (SCREEN_HEIGHT >> 1);
	
	if (player->tdy == -1) scrollLevelU(&level0, x, y);
	else if (player->tdy == 1) scrollLevelD(&level0, x, y);
	if (player->tdx == -1) scrollLevelL(&level0, x, y);
	else if (player->tdx == 1) scrollLevelR(&level0, x, y);
}

Level::Level(LevelData_t* level) {
	//Free old level
	delete entities;
	
	//Load new level
	//Clear OAM
	for (int i = 0; i < 128; i++) {
		OAM[i] = {ATTR0_DISABLED, 0, 0, 0};
	}
	
	//Enable backgrounds
	REG_DISPCNT = MODE_0 | level->bgEnable | OBJ_ON | OBJ_1D_MAP;
	
	//Load entity tiles and palettes
	for (int i = 0; i < level->numDiffEntities; i++) {
		loadTileToMem(&(level->entityTiles[i]), i, OBJ_BLOCK);
	}
	
	//Create entities based on EntityData
	numEnt = level->numEntities;
	entities = (Entity**)malloc(numEnt * sizeof(Entity*));
	for (int i = 0; i < numEnt; i++) {
		EntityData_t ed = level->entities[i];
		
		switch(ed.type) {
			case EntityTypes::player: {
					entities[i] = new Player(ed.x, ed.y, &(OAM[i]), i);
					break;
				}
			
			default:
				break;
		}
	}
	player = entities[0];
	//x = player->x;
	//y = player->y;
	
	//Load level tiles
	loadTileToMem(level->levelTileCharacterData, 0, 0);
	
	//Load level
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
			
			if (yS < 0 || xS < 0 || yS >= level->levelScreenData->height || xS >= level->levelScreenData->width) {
				((u16*) SCREEN_BASE_BLOCK(8))[xD + yD * VIRTUAL_SCREEN_TILE_SIZE] = level->levelScreenData->defaultTile; //BG0
				((u16*) SCREEN_BASE_BLOCK(9))[xD + yD * VIRTUAL_SCREEN_TILE_SIZE] = level->levelScreenData->defaultTile; //BG1
			} else {
				((u16*) SCREEN_BASE_BLOCK(8))[xD + yD * VIRTUAL_SCREEN_TILE_SIZE] = level->levelScreenData->screenData[0][xS + yS * level->levelScreenData->width]; //BG0
				((u16*) SCREEN_BASE_BLOCK(9))[xD + yD * VIRTUAL_SCREEN_TILE_SIZE] = level->levelScreenData->screenData[1][xS + yS * level->levelScreenData->width]; //BG1
			}
			
			xD++;
			xS++;
		}
		
		yD++;
		yS++;
	}
}

inline Entity* Level::getEntity(u8 index) {
	return entities[index];
}