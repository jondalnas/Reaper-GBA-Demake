#pragma once
#include <gba_types.h>
#include <gba_sprites.h>

#include "gfx/Tile.h"

class Level;

class Entity {
public:
	u32 x, y; //Fixed point 16-16
	u8 tx, ty;
	short tdx, tdy;
	
	Entity(u32 x, u32 y, u8 radius, Level* level);
	virtual ~Entity();
	
	virtual void update();
	virtual void melee(Entity* e) = 0;
	virtual u8 collides(Entity* e);
	virtual u8 teleport() {
		return 0;
	}
	virtual u8 takeOver() {
		return 0;
	}
	virtual void unTakeOver() {}
	
	u8 isLineToEntityBlocked(Entity* e);
	void move(int dx, int dy);
	
	inline u8 getRadius() {
		return _radius;
	}
	
protected:
	u8 _radius;
	Level* _level;
	OBJATTR* _attributeObj;
	u8 _entityOAM;
};