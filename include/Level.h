#pragma once

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
	void init(LevelData_t* level);
	Entity* getEntity(u8 index);
	
	~Level() {
		delete entities;
	}

private:
	Entity* entities;
	Entity* player;
};