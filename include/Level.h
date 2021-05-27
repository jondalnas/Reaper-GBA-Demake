#pragma once

#include <stdlib.h>
#include <gba_types.h>

#include "Entity.h"

typedef struct {
	u16 bgEnable;
	const u8 numEntities;
	const EntityData_t* entities;
	const u8 numDiffEntities;
	const tile_t* entityTiles;
	const tile_t* levelTileCharacterData;
	const u16* levelTileScreenData[1024];
} LevelData_t;

class Level {
public:
	Level() {
	}

	void init(LevelData_t* level);
	Entity* getEntity(u8 index);
	void update();
	
	~Level() {
		delete entities;
	}

private:
	Entity* entities;
	u8 numEnt;
	Entity* player;
};