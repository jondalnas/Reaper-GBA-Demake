#pragma once
#include <gba_types.h>
#include <gba_sprites.h>

#include "gfx/Tile.h"

enum EntityTypes {
	player
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
	
	Entity(unsigned short x, unsigned short y, OBJATTR* attributeObj) : x(x), y(y), _attributeObj(attributeObj) {}
	
	virtual ~Entity() {}
	
	virtual void update();
protected:
	OBJATTR* _attributeObj;
};