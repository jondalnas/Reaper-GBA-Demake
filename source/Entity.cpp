#include "Entity.h"
#include "Level.h"

Entity::Entity(u32 x, u32 y, u8 radius, Level* level) : x(x), y(y), _radius(radius), _level(level) {
	_entityOAM = _level->lendOAM();
	_attributeObj = &(OAM[_entityOAM]);
}

Entity::~Entity() {
	_level->giveOAMBack(_entityOAM);
}

void Entity::update() {
	tdx = tdy = 0;
	u8 newTX = x >> (3 + 16), newTY = y >> (3 + 16);
	if (tx != newTX) {
		if (tx < newTX) {
			tdx = 1;
		} else {
			tdx = -1;
		}
		
		tx = newTX;
	}
	
	if (ty != newTY) {
		if (ty < newTY) {
			tdy = 1;
		} else {
			tdy = -1;
		}
		
		ty = newTY;
	}
}

void Entity::move(int dx, int dy) {
	if (dx != 0 && dy != 0) {
		move((dx >> 1) | (dx < 0 ? 0x80000000 : 0), 0);
		move(0, (dy >> 1) | (dy < 0 ? 0x80000000 : 0));
	}
	
	for (u8 i = 0; i < _level->getNumEntites(); i++) {
		Entity* e = _level->getEntity(i);
		
		if (e == this) continue;
		
		if (((x + dx) >> 16) - _radius < (e->x >> 16) + e->getRadius() && ((x + dx) >> 16) + _radius > (e->x >> 16) - e->getRadius() &&
			((y + dy) >> 16) - _radius < (e->y >> 16) + e->getRadius() && ((y + dy) >> 16) + _radius > (e->y >> 16) - e->getRadius()) {
				if (e->collides(this)) {
					collides(e);
					return;
				}
			}
	}

	u8 tx0 = (((x + dx) >> 16) - _radius) >> 3;
	u8 ty0 = (((y + dy) >> 16) - _radius) >> 3;
	u8 tx1 = (((x + dx) >> 16) + _radius) >> 3;
	u8 ty1 = (((y + dy) >> 16) + _radius) >> 3;
	
	//If outside screen, then return
	if (tx0 >= _level->_width || tx1 >= _level->_width || ty0 >= _level->_height || ty1 >= _level->_height) return;
	
	//Offset by 4 pixels, because all collision layers are as well
	tx0 = (((x + dx) >> 16) - 4 - _radius) >> 3;
	ty0 = (((y + dy) >> 16) - 4 - _radius) >> 3;
	tx1 = (((x + dx) >> 16) - 4 + _radius) >> 3;
	ty1 = (((y + dy) >> 16) - 4 + _radius) >> 3;
	
	for (u8 yy = ty0; yy <= ty1; yy++) {
		for (u8 xx = tx0; xx <= tx1; xx++) {
			if (_level->getTileFlag(xx, yy) & TILE_FLAG_SOLID) return;
		}
	}
	
	x += dx;
	y += dy;
}

u8 Entity::isLineToEntityBlocked(Entity* e) {
	short dx = (short)e->tx - tx;
	short dy = (short)e->ty - ty;
	
	u8 ndx = 0, ndy = 0;
	
	//Flip dx and dy
	if (dx < 0) {
		dx = -dx;
		ndx = 1;
	}
	
	if (dy < 0) {
		dy = -dy;
		ndy = 1;
	}
	
	//Convert to fixed point 8-8
	dx <<= 8;
	dy <<= 8;
	
	//The number of times, xx and yy sound be added to a register to get to other entity
	u8 length = 1;
	
	//Right shift so the line is drawn with at most steps of 1 tile, left shift length to double length of line, as we half the step amount
	while((dx & 0xFF00) || (dy & 0xFF00)) {
		dx >>= 1;
		dy >>= 1;
		length <<= 1;
		
		//If length of line is too long, then return that the line is blocked
		if (length >= 128) return 1;
	}
	
	short xx = tx << 8, yy = ty << 8;
	//Check if current tile is solid and not transparent
	u8 flag = _level->getTileFlag(xx >> 8, yy >> 8);
	if ((flag & TILE_FLAG_SOLID) && !(flag & TILE_FLAG_TRANSPARENT)) return 1;
	
	//Flip dx and dy black to normal
	if (ndx) {
		dx = -dx;
	}
	
	if (ndy) {
		dy = -dy;
	}
	
	for (u8 i = 0; i < length; i++) {
		xx += dx;
		yy += dy;
		
		//If tile is solid and not transparent, then line is blocked
		flag = _level->getTileFlag(xx >> 8, yy >> 8);
		if ((flag & TILE_FLAG_SOLID) && !(flag & TILE_FLAG_TRANSPARENT)) return 1;
	}
	
	return 0;
}

u8 Entity::collides(Entity* e) {
	return 0;
}

/*void Entity::init(EntityData_t* entityData) {
	_attributeObj->attr0 = y | (entityData->rotScale << 8) | (entityData->doubleMode << 9) | ((entityData->OBJMode & 3) << 10) | (entityData->mosaic << 12) | (entityData->colorMode << 13) | ((entityData->shape & 3) << 14);
	_attributeObj->attr1 = x | ((entityData->rotScaleParam & 31) << 9) | (entityData->flipH << 12) | (entityData->flipH << 13) | ((entityData->size & 3) << 14);
	_attributeObj->attr2 = entityData->characterName | OBJ_PRIORITY(entityData->priority & 3) | OBJ_PALETTE(entityData->paleteBank & 15);
}*/