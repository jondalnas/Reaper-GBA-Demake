#include "Player.h"

#include <gba_input.h>
#include <vector>

#include "Math.h"
#include "Level.h"
#include "Enemy.h"

#define PLAYER_ROT_SPEED 6
#define PLAYER_MOV_SPEED (2 << 16)

#define PLAYER_ATK_COOLDOWN 20

Player::Player(u32 x, u32 y, Level* level, OBJATTR* attributeObj, OBJATTR* scytheAttributeObj, OBJATTR* swingAttributeObj, u8 entityNum) : Entity(x, y, 3, level, attributeObj), _entityNum(entityNum), _scytheAttributeObj(scytheAttributeObj), _swingAttributeObj(swingAttributeObj) {
	//Init player to center of screen
	_attributeObj->attr0 = 72 | OBJ_ROT_SCALE_ON | OBJ_MODE(0) | OBJ_16_COLOR | ATTR0_SQUARE;
	_attributeObj->attr1 = 112 | ATTR1_ROTDATA(entityNum) | ATTR1_SIZE_16;
	_attributeObj->attr2 = 0 | OBJ_PRIORITY(0) | OBJ_PALETTE(0);
	
	_affine = &(((OBJAFFINE*) 0x07000000)[entityNum]);
	short cos = Math::cos(_rot);
	short sin = Math::sin(_rot);
	_affine->pa = cos;
	_affine->pb = sin;
	_affine->pc = -sin;
	_affine->pd = cos;
	
	//Init scythe to player hand with same rotation as player
	_scytheAttributeObj->attr0 = (72 + ((sin >> 7) | (sin < 0 ? 0xC000 : 0x0000))) | OBJ_ROT_SCALE_ON | OBJ_MODE(0) | OBJ_16_COLOR | ATTR0_SQUARE;
	_scytheAttributeObj->attr1 = (111 + ((cos >> 7) | (cos < 0 ? 0xC000 : 0x0000))) | ATTR1_ROTDATA(entityNum) | ATTR1_SIZE_16;
	_scytheAttributeObj->attr2 = 8 | OBJ_PRIORITY(0) | OBJ_PALETTE(0);
	
	_swingAttributeObj->attr0 = (72 + ((sin >> 7) | (sin < 0 ? 0xF800 : 0x0000))) | OBJ_ROT_SCALE_ON | OBJ_MODE(0) | OBJ_16_COLOR | ATTR0_SQUARE;
	_swingAttributeObj->attr1 = (111 + ((cos >> 7) | (cos < 0 ? 0xF800 : 0x0000))) | ATTR1_ROTDATA(entityNum) | ATTR1_SIZE_16;
	_swingAttributeObj->attr2 = 12 | OBJ_PRIORITY(0) | OBJ_PALETTE(0);
	
	_swingAttributeObjATTR0 = _swingAttributeObj->attr0;
}

void Player::update() {
	short sin = Math::sin(_rot);
	short cos = Math::cos(_rot);
	
	scanKeys();
	
	//DPAD
	if (REG_KEYINPUT & DPAD) {
		move((REG_KEYINPUT & KEY_RIGHT) ? ((REG_KEYINPUT & KEY_LEFT) ? 0 : -PLAYER_MOV_SPEED) : PLAYER_MOV_SPEED, (REG_KEYINPUT & KEY_DOWN) ? ((REG_KEYINPUT & KEY_UP) ? 0 : -PLAYER_MOV_SPEED) : PLAYER_MOV_SPEED);
	}
	
	//BACK BUTTONS
	if (!(REG_KEYINPUT & KEY_R)) {
		_rot += PLAYER_ROT_SPEED;
		
		if (_rot > 359) _rot -= 360;
	} else if (!(REG_KEYINPUT & KEY_L)) {
		_rot -= PLAYER_ROT_SPEED;
		
		if (_rot > 359) _rot += 360;
	}
	
	//A BUTTON
	_swingCooldown++;
	if (_swingCooldown > PLAYER_ATK_COOLDOWN) {
		//Disable swing sprite if attack is ready
		_swingAttributeObj->attr0 = ATTR0_DISABLED;
		
		if (!(REG_KEYINPUT & KEY_A)) {
			std::vector<Entity*>* entities = _level->getEntitiesInside(((sin >> 5) | (sin < 0 ? 0xF800 : 0x0000)) + (x >> 16), -((cos >> 5) | (cos < 0 ? 0xF800 : 0x0000)) + (y >> 16), 16, 16);
			
			for (u8 i = 0; i < entities->size(); i++) {
				(*entities)[i]->collideWithScythe();
			}
			
			delete entities;
			
			//Re-enable swing
			_swingCooldown = 0;
			_swingAttributeObj->attr0 = _swingAttributeObjATTR0;
		}
	}
	
	//Update scythe and swing
	_scytheAttributeObj->attr0 &= ~0x00FF;
	_scytheAttributeObj->attr0 |= (72 + ((sin >> 7) | (sin < 0 ? 0xFE00 : 0x0000))) & 0x00FF;
	_scytheAttributeObj->attr1 &= ~0x01FF;
	_scytheAttributeObj->attr1 |= (112 + ((cos >> 7) | (cos < 0 ? 0xFE00 : 0x0000))) & 0x01FF;
	
	if (_swingCooldown <= PLAYER_ATK_COOLDOWN) {
		_swingAttributeObj->attr0 &= ~0x00FF;
		_swingAttributeObj->attr0 |= (72 + ((cos >> 7) | (sin < 0 ? 0xFC00 : 0x0000))) & 0x00FF;
		_swingAttributeObj->attr1 &= ~0x01FF;
		_swingAttributeObj->attr1 |= (112 + ((cos >> 7) | (cos < 0 ? 0xFC00 : 0x0000))) & 0x01FF;
	}
	
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
	
	_affine->pa = cos;
	_affine->pb = sin;
	_affine->pc = -sin;
	_affine->pd = cos;
}