#include "Player.h"

#include <gba_input.h>

Player::Player(unsigned short x, unsigned short y, OBJATTR* attributeObj, u8 entityNum) : Entity(x, y, attributeObj) {
	_attributeObj->attr0 = y /*| OBJ_ROT_SCALE_ON */| OBJ_MODE(0) | OBJ_16_COLOR | ATTR0_SQUARE;
	_attributeObj->attr1 = x | ATTR1_ROTDATA(entityNum) | ATTR1_SIZE_16;
	_attributeObj->attr2 = 0 | OBJ_PRIORITY(0) | OBJ_PALETTE(0);
}

void Player::update() {
	scanKeys();
	
	if (REG_KEYINPUT & DPAD) {
		x += (REG_KEYINPUT & KEY_RIGHT) ? ((REG_KEYINPUT & KEY_LEFT) ? 0 : -1) : 1;
		y += (REG_KEYINPUT & KEY_DOWN) ? ((REG_KEYINPUT & KEY_UP) ? 0 : -1) : 1;
	}
	_attributeObj->attr0 &= ~0x00ff; //0x00ff = y bitmask
	_attributeObj->attr0 |= y & 0x00ff;
	_attributeObj->attr1 &= ~0x01ff; //0x01ff = x bitmask
	_attributeObj->attr1 |= x & 0x01ff;

	Entity::update();
}