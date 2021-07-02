#include "Player.h"

#include <gba_input.h>
#include <vector>

#include "Math.h"
#include "Level.h"
#include "Enemy.h"

#define PLAYER_ROT_SPEED 6
#define PLAYER_MOV_SPEED (2 << 16)

#define PLAYER_ATK_COOLDOWN 20
#define PLAYER_MAX_TRW_TIME 180
#define PLAYER_TRW_BTN_DOWN_TIME 20

Player::Player(u32 x, u32 y, Level* level, OBJATTR* attributeObj, u8 playerOAM, OBJATTR* scytheAttributeObj, u8 scytheOAM, OBJATTR* swingAttributeObj, u8 swingOAM, u8 entityNum) : Entity(x, y, 3, level, attributeObj, playerOAM), _entityNum(entityNum), _scytheOAM(scytheOAM), _swingOAM(swingOAM), _scytheAttributeObj(scytheAttributeObj), _swingAttributeObj(swingAttributeObj) {
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
	
	_scytheAttributeObjATTR0 = _scytheAttributeObj->attr0 & 0xFF00;
	
	_swingAttributeObj->attr0 = (72 + ((sin >> 7) | (sin < 0 ? 0xF800 : 0x0000))) | OBJ_ROT_SCALE_ON | OBJ_MODE(0) | OBJ_16_COLOR | ATTR0_SQUARE;
	_swingAttributeObj->attr1 = (111 + ((cos >> 7) | (cos < 0 ? 0xF800 : 0x0000))) | ATTR1_ROTDATA(entityNum) | ATTR1_SIZE_16;
	_swingAttributeObj->attr2 = 12 | OBJ_PRIORITY(0) | OBJ_PALETTE(0);
	
	_swingAttributeObjATTR0 = _swingAttributeObj->attr0 & 0xFF00;
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
	if (_swingCooldown <= PLAYER_ATK_COOLDOWN) _swingCooldown++;
	if (_throwTime <= PLAYER_MAX_TRW_TIME) _throwTime++;
	
	if (_swingCooldown > PLAYER_ATK_COOLDOWN && _throwTime > PLAYER_MAX_TRW_TIME) {
		//Disable swing sprite if attack is ready
		_swingAttributeObj->attr0 = ATTR0_DISABLED;
		
		//Falling edge detection
		if (!(REG_KEYINPUT & KEY_A)) {
			if (_throwButtonHoldDown < PLAYER_TRW_BTN_DOWN_TIME) _throwButtonHoldDown++;
		} else {
			if (!_lastA) {
				if (_throwButtonHoldDown < PLAYER_TRW_BTN_DOWN_TIME) {
					std::vector<Entity*>* entities = _level->getEntitiesInside(((sin >> 5) | (sin < 0 ? 0xF800 : 0x0000)) + (x >> 16), -((cos >> 5) | (cos < 0 ? 0xF800 : 0x0000)) + (y >> 16), 16, 16);
					
					for (u8 i = 0; i < entities->size(); i++) {
						(*entities)[i]->collideWithScythe();
					}
					
					delete entities;
					
					//Re-enable swing
					_swingCooldown = 0;
					_swingAttributeObj->attr0 = _swingAttributeObjATTR0;
				} else {
					_throwTime = 0;
					
					//Reset scythe position to player position
					_scytheX = x >> 16;
					_scytheY = y >> 16;
					
					//Update scythe direction
					_scytheDX = (sin >> 6) | (sin < 0 ? 0xFC : 0x00);
					_scytheDY = -((cos >> 6) | (cos < 0 ? 0xFC : 0x00));
				}
			}
			
			_throwButtonHoldDown = 0;
		}
		
		_lastA = REG_KEYINPUT & KEY_A;
	}
	
	//Update scythe and swing position
	if (_throwTime > PLAYER_MAX_TRW_TIME) {
		//Scythe not thrown
		_scytheAttributeObj->attr0 = _scytheAttributeObjATTR0;
		_scytheAttributeObj->attr0 |= (72 + ((sin >> 7) | (sin < 0 ? 0xFE00 : 0x0000))) & 0x00FF;
		_scytheAttributeObj->attr1 &= ~0x01FF;
		_scytheAttributeObj->attr1 |= (112 + ((cos >> 7) | (cos < 0 ? 0xFE00 : 0x0000))) & 0x01FF;
	} else {
		//Scythe thrown
		//Update position
		_scytheX += _scytheDX;
		_scytheY += _scytheDY;
		
		//Get tile position
		u8 xt = _scytheX >> 3;
		u8 yt = _scytheY >> 3;
		
		//Check if scythe collides with level
		if (_level->getTileFlag(xt + 0, yt + 0) & TILE_FLAG_SOLID ||
			_level->getTileFlag(xt + 1, yt + 0) & TILE_FLAG_SOLID ||
			_level->getTileFlag(xt + 0, yt + 1) & TILE_FLAG_SOLID ||
			_level->getTileFlag(xt + 1, yt + 1) & TILE_FLAG_SOLID ||
			xt >= _level->_width || yt >= _level->_height) {
			//If scythe collides with wall or boundries, then reset it to player hands
			_throwTime = 255;
		} else {
			//If not, then see if it collides with enemies
			std::vector<Entity*>* entities = _level->getEntitiesInside(_scytheX, _scytheY, 16, 16);
			
			for (u8 i = 0; i < entities->size(); i++) {
				(*entities)[i]->collideWithScythe();
			}
			
			delete entities;
			
			//Get screen position
			short sx = _scytheX - 8 - _level->getX();
			short sy = _scytheY - 8 - _level->getY();
			
			if (sx < -16 || sy < -16 || sx >= SCREEN_WIDTH + 32 || sy >= SCREEN_HEIGHT + 32) {
				_scytheAttributeObj->attr0 = ATTR0_DISABLED;
			} else {
				_scytheAttributeObj->attr0 = _scytheAttributeObjATTR0;
				_scytheAttributeObj->attr0 |= sy & 0x00FF;
				_scytheAttributeObj->attr1 &= ~0x01FF;
				_scytheAttributeObj->attr1 |= sx & 0x01FF;
			}
		}
	}
	
	if (_swingCooldown <= PLAYER_ATK_COOLDOWN) {
		_swingAttributeObj->attr0 &= ~0x00FF;
		_swingAttributeObj->attr0 |= (72 - ((sin >> 7) | (sin < 0 ? 0xFC00 : 0x0000)) - ((cos >> 5) | (cos < 0 ? 0xF800 : 0x0000))) & 0x00FF;
		_swingAttributeObj->attr1 &= ~0x01FF;
		_swingAttributeObj->attr1 |= (112 + ((cos >> 7) | (cos < 0 ? 0xFE00 : 0x0000)) + ((sin >> 5) | (sin < 0 ? 0xF800 : 0x0000))) & 0x01FF;
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
	
	//Update player rotation
	_affine->pa = cos;
	_affine->pb = sin;
	_affine->pc = -sin;
	_affine->pd = cos;
}