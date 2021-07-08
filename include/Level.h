#pragma once

#include <stdlib.h>
#include <gba_types.h>
#include <vector>
#include <stack>

#include "gfx/LevelHandler.h"
#include "gfx/Palette.h"
#include "Entity.h"
#include "Player.h"

#define TILE_FLAG_SOLID 0x01
#define TILE_FLAG_TRANSPARENT 0x02

class Entity;

class Level {
public:
	Level(const LevelData_t* level);
	
	u16 _width, _height;

	void update();
	std::vector<Entity*>* getEntitiesInside(u16 x, u16 y, u16 w, u16 h);

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
	
	inline const level_t* getLevel() {
		return _level;
	}
	
	inline u8 lendOAM() {
		if (_OAMNum->empty()) return 0;
		
		u8 OAMNum = _OAMNum->top();
		_OAMNum->pop();
		return OAMNum;
	}
	
	inline void giveOAMBack(u8 OAMNum) {
		_OAMNum->push(OAMNum);
		OAM[OAMNum].attr0 = ATTR0_DISABLED;
	}
	
	inline void freeze() {
		timeFrozen = 1;
		loadGrayscalePalettesToMem();
	}
	
	inline void unfreeze() {
		timeFrozen = 0;
		loadPalettesToMem();
	}
	
	inline u8 isTimeFrozen() {
		return timeFrozen;
	}

	inline void restart() {
		_restart = 1;
	}

	inline u8 shouldRestart() {
		return _restart;
	}
	
	~Level() {
		for (auto e : _entities) {
			delete e;
		}
		_entities.clear();
		
		delete _OAMNum;
	}

private:
	u16 _x = 0, _y = 0;
	
	const u8* _tileFlags;
	const level_t* _level;

	u8 _restart = 0;
	
	std::vector<Entity*> _entities = {};
	u8 _numEnt = 0;
	std::stack<u8>* _OAMNum;
	Player* _player = nullptr;
	
	u8 timeFrozen = 0;
};