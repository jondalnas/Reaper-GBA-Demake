#pragma once

#include <stdlib.h>
#include <gba_types.h>

#include "Entity.h"
#include "gfx/LevelHandler.h"

typedef struct {
	u16 bgEnable;
	const u8 numEntities;
	const EntityData_t* entities;
	const u8 numDiffEntities;
	const tile_t* entityTiles;
	const tile_t* levelTileCharacterData;
	const level_t* levelScreenData;
} LevelData_t;

class Level {
public:
	Level(LevelData_t* level);

	inline Entity* getEntity(u8 index);
	void update();
	
	~Level() {
		if (entities != NULL) delete entities;
	}

private:
	u16 x, y;
	
	Entity** entities = NULL;
	u8 numEnt;
	Entity* player;
};