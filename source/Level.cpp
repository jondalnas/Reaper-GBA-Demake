#include "Level.h"

#include <gba_video.h>
#include <gba_sprites.h>
#include <stdlib.h>

void Level::update() {
	for (int i = 0; i < numEnt; i++) {
		entities[i].update();
	}
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
	entities = (Entity*)malloc(numEnt * sizeof(Entity));
	for (int i = 0; i < numEnt; i++) {
		EntityData_t ed = level->entities[i];
		Entity e(ed.x, ed.y, &(OAM[i]));
		entities[i] = e;
		entities[i].init(&ed);
	}
	player = &(entities[0]);
	//*((vu32*)0x02000104) = (u32)&level->numEntities;
	*((vu32*)0x02000100) = (u32)&numEnt;
	
	//Load level tiles
	loadTileToMem(level->levelTileCharacterData, 0, 0);
	
	//Load level
	for (int i = 0; i < 1024; i++) {
		((u16*) SCREEN_BASE_BLOCK(8))[i] = (*(level->levelTileScreenData))[i];
	}
}

Entity* Level::getEntity(u8 index) {
	return &(entities[index]);
}