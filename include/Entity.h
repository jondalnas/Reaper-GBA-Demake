#pragma once
#include <gba_types.h>
#include <gba_sprites.h>

#include "gfx/Tile.h"

class Level;

enum EntityTypes {
	player,
	brawler
};

typedef struct {
	u16 x;
	u16 y;
	EntityTypes type;
} EntityData_t;

class Entity {
public:
	u16 x, y;
	u8 tx, ty;
	short tdx, tdy;
	
	Entity(unsigned short x, unsigned short y, u8 radius, Level* level, OBJATTR* attributeObj) : x(x), y(y), _radius(radius), _level(level), _attributeObj(attributeObj) {}
	virtual ~Entity() {}
	
	virtual void update();
protected:
	u8 _radius;
	Level* _level;
	OBJATTR* _attributeObj;
	
	void move(short dx, short dy);
};