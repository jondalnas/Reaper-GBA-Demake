#pragma once
#include <gba_types.h>
#include <gba_sprites.h>

#include "gfx/Tile.h"

typedef struct {
	u16 x;
	u16 y;
	u8 shape;
	bool colorMode;
	bool mosaic;
	u8 OBJMode;
	bool doubleMode;
	bool rotScale;
	u8 size;
	bool flipH;
	bool flipV;
	u8 rotScaleParam;
	u8 paleteBank;
	u8 priority;
	u8 characterName;
} EntityData_t;

class Entity {
public:
	Entity(unsigned short x, unsigned short y, OBJATTR* attributeObj) : x(x), y(y), _attributeObj(attributeObj) {}
	~Entity() {}

	unsigned short x;
	unsigned short y;
	
	void update();
	
	void init(EntityData_t* entityData);
private:
	OBJATTR* _attributeObj;
};