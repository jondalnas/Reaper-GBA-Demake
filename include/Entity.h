#pragma once
#include <gba_types.h>
#include <gba_sprites.h>

#include "gfx/tile.h"

class Entity {
public:
	Entity(unsigned short x, unsigned short y, OBJATTR* attributeObj, const u16 tileOffs, const tile_t* tile_p) : x(x), y(y), _attributeObj(attributeObj) {
		loadTileToMem(tile_p, tileOffs, OBJ_BLOCK);
	}

	unsigned short x;
	unsigned short y;
	
	void update();
	
	void init(u8 shape, bool colorMode, bool mosaic, u8 OBJMode, bool doubleMode, bool rotScale, u8 size, bool flipH, bool flipV, u8 rotScaleParam, u8 paleteBank, u8 priority, u8 characterName);
private:
	OBJATTR* _attributeObj;
};