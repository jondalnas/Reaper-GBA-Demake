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
	u32 x; //Fixed point 16-16
	u32 y; //Fixed point 16-16
	EntityTypes type;
} EntityData_t;

class Entity {
public:
	u32 x, y; //Fixed point 16-16
	u8 tx, ty;
	short tdx, tdy;
	
	Entity(u32 x, u32 y, u8 radius, Level* level, OBJATTR* attributeObj) : x(x), y(y), _radius(radius), _level(level), _attributeObj(attributeObj) {}
	virtual ~Entity() {}
	
	virtual void update();
	
	u8 isLineToEntityBlocked(Entity* e);
	
	inline u8 getRadius() {
		return _radius;
	}
protected:
	u8 _radius;
	Level* _level;
	OBJATTR* _attributeObj;
	
	void move(int dx, int dy);
};