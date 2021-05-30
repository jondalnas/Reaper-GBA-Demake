#include "Level.h"
#include "Player.h"

#include <gba_video.h>
#include <gba_sprites.h>
#include <stdlib.h>

void Level::update() {
	for (int i = 0; i < numEnt; i++) {
		entities[i]->update();
	}
	
	BG_OFFSET[0].x = player->x;
	BG_OFFSET[0].y = player->y;
	BG_OFFSET[1].x = player->x;
	BG_OFFSET[1].y = player->y;
	BG_OFFSET[2].x = player->x;
	BG_OFFSET[2].y = player->y;
}

void Level::init(LevelData_t* level) {
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
				return;
		}
	}
	player = entities[0];
	
	//Load level tiles
	loadTileToMem(level->levelTileCharacterData, 0, 0);
	
	//Load level
	for (int i = 0; i < 1024; i++) {
		((u16*) SCREEN_BASE_BLOCK(8))[i] = (*(level->levelTileScreenData))[i];
	}
}

inline Entity* Level::getEntity(u8 index) {
	return entities[index];
}