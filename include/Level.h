#pragma once

#include <stdlib.h>
#include <gba_types.h>

#include "gfx/LevelHandler.h"
#include "Entity.h"

class Entity;

typedef struct {
	u16 bgEnable;
	const u16 width;
	const u16 height;
	const u8 numEntities;
	const EntityData_t** entities;
	const u8 numDiffEntities;
	const tile_t** entityTiles;
	const tile_t* levelTileCharacterData;
	const level_t* levelScreenData;
	const u8* tileFlags;
} LevelData_t;

class Level {
public:
	Level(LevelData_t* level);
	
	u16 _width, _height;

	void update();

	inline Entity* getEntity(u8 index) {
		return _entities[index];
	}

	inline u8 getTileFlag(u8 x, u8 y) {
		return _tileFlags[x + y * _width];
	}
	
	inline u8 getNumEntites() {
		return _numEnt;
	}
	
	inline u16 getX() {
		return _x;
	}
	
	inline u16 getY() {
		return _y;
	}
	
	~Level() {
		if (_entities != NULL) {
			for (u8 i = 0; i < _numEnt; i++) delete _entities[i];
			delete _entities;
		}
	}

private:
	u16 _x, _y;
	
	const u8* _tileFlags;
	
	Entity** _entities = NULL;
	u8 _numEnt;
	Entity* _player;
};