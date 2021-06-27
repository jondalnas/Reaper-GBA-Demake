#include "Brawler.h"

#include "Math.h"
#include "Level.h"

#define BRAWLER_ROT_SPEED 6

Brawler::Brawler(unsigned short x, unsigned short y, Level* level, OBJATTR* attributeObj, u8 entityNum) : Entity(x, y, 4, level, attributeObj), _entityNum(entityNum) {
	_attributeObj->attr0 = x | OBJ_ROT_SCALE_ON | OBJ_MODE(0) | OBJ_16_COLOR | ATTR0_SQUARE;
	_attributeObj->attr1 = y | ATTR1_ROTDATA(entityNum) | ATTR1_SIZE_16;
	_attributeObj->attr2 = 4 | OBJ_PRIORITY(0) | OBJ_PALETTE(0);
	
	_initialAttribute = *_attributeObj;
	
	_affine = &(((OBJAFFINE*) 0x07000000)[entityNum]);
	_affine->pa = getCos(_rot);
	_affine->pb = getSin(_rot);
	_affine->pc = -getSin(_rot);
	_affine->pd = getCos(_rot);
}

void Brawler::update() {
	_rot += BRAWLER_ROT_SPEED;
	if (_rot >= 360) _rot -= 360;
	
	//move(1, 0);

	u16 cos = getCos(_rot);
	u16 sin = getSin(_rot);
	_affine->pa = cos;
	_affine->pb = sin;
	_affine->pc = -sin;
	_affine->pd = cos;
	
	short sx = x - 8 - _level->getX();
	short sy = y - 8 - _level->getY();
	
	if (sx < -16 || sy < -16 || sx >= SCREEN_WIDTH + 16 || sy >= SCREEN_HEIGHT + 16) {
		_attributeObj->attr0 = ATTR0_DISABLED;
	} else {
		_attributeObj->attr0 = (sy & 0x00FF) | (_initialAttribute.attr0 & 0xFF00);
		_attributeObj->attr1 = (sx & 0x01FF) | (_initialAttribute.attr1 & 0xFE00);
	}
}