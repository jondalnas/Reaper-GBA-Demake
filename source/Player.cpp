#include "Player.h"

#include <gba_input.h>

#include "Math.h"

#define PLAYER_ROT_SPEED 6

Player::Player(unsigned short x, unsigned short y, Level* level, OBJATTR* attributeObj, u8 entityNum) : Entity(x, y, 4, level, attributeObj), _entityNum(entityNum) {
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
		move((REG_KEYINPUT & KEY_RIGHT) ? ((REG_KEYINPUT & KEY_LEFT) ? 0 : -1) : 1, (REG_KEYINPUT & KEY_DOWN) ? ((REG_KEYINPUT & KEY_UP) ? 0 : -1) : 1);
	}
	
	//BACK BUTTONS
	if (!(REG_KEYINPUT & KEY_R)) {
		_rot += PLAYER_ROT_SPEED;
		
		if (_rot > 359) _rot -= 360;
	} else if (!(REG_KEYINPUT & KEY_L)) {
		_rot -= PLAYER_ROT_SPEED;
		
		if (_rot > 359) _rot += 360;
	}
	
	tdx = tdy = 0;
	u8 newTX = x >> 3, newTY = y >> 3;
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
	
	_affine->pa = getCos(_rot);
	_affine->pb = getSin(_rot);
	_affine->pc = -getSin(_rot);
	_affine->pd = getCos(_rot);
}