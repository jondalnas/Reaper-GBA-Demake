#include "Player.h"

#include <gba_input.h>

#include "Math.h"

#define PLAYER_ROT_SPEED 3

Player::Player(unsigned short x, unsigned short y, OBJATTR* attributeObj, u8 entityNum) : Entity(x, y, attributeObj), _entityNum(entityNum) {
	_attributeObj->attr0 = 72 | OBJ_ROT_SCALE_ON | OBJ_MODE(0) | OBJ_16_COLOR | ATTR0_SQUARE;
	_attributeObj->attr1 = 112 | ATTR1_ROTDATA(entityNum) | ATTR1_SIZE_16;
	_attributeObj->attr2 = 0 | OBJ_PRIORITY(0) | OBJ_PALETTE(0);
	
	_affine = &(((OBJAFFINE*) 0x07000000)[entityNum]);
	_affine->pa = getCos(_rot);
	_affine->pb = getSin(_rot);
	_affine->pc = -getSin(_rot);
	_affine->pd = getCos(_rot);
}

void Player::update() {
	scanKeys();
	
	//DPAD
	if (REG_KEYINPUT & DPAD) {
		x += (REG_KEYINPUT & KEY_RIGHT) ? ((REG_KEYINPUT & KEY_LEFT) ? 0 : -1) : 1;
		y += (REG_KEYINPUT & KEY_DOWN) ? ((REG_KEYINPUT & KEY_UP) ? 0 : -1) : 1;
	}
	
	//BACK BUTTONS
	if (!(REG_KEYINPUT & KEY_R)) {
		_rot += PLAYER_ROT_SPEED;
		
		if (_rot > 359) _rot -= 360;
	} else if (!(REG_KEYINPUT & KEY_L)) {
		_rot -= PLAYER_ROT_SPEED;
		
		if (_rot > 359) _rot += 360;
	}
	
	_affine->pa = getCos(_rot);
	_affine->pb = getSin(_rot);
	_affine->pc = -getSin(_rot);
	_affine->pd = getCos(_rot);
}