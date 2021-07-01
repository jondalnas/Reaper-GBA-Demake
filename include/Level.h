#pragma once

#include <stdlib.h>
#include <gba_types.h>
#include <vector>

#include "gfx/LevelHandler.h"
#include "Entity.h"
#include "Player.h"

#define TILE_FLAG_SOLID 0x01
#define TILE_FLAG_TRANSPARENT 0x02

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
	
	inline Player* getPlayer() {
		return _player;
	}
	
	~Level() {
		for (auto e : _entities) {
			delete e;
		}
		_entities.clear();
	}

private:
	u16 _x, _y;
	
	const u8* _tileFlags;
	
	std::vector<Entity*> _entities = {};
	u8 _numEnt;
	Player* _player;
};