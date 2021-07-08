#include "Player.h"

#include <gba_input.h>
#include <vector>

#include "FixedPointMath.h"
#include "Level.h"
#include "Enemy.h"

#define PLAYER_ROT_SPEED 6
#define PLAYER_MOV_SPEED (2 << 16)

#define PLAYER_ATK_COOLDOWN 20
#define PLAYER_MAX_TRW_TIME 180
#define PLAYER_TRW_BTN_DOWN_TIME 20

#define PLAYER_CSR_SPEED 2

Player::Player(u32 x, u32 y, Level* level, u8 entityNum) : Entity(x, y, 3, level), _entityNum(entityNum) {
	//Init player to center of screen
	_attributeObj->attr0 = 72 | OBJ_ROT_SCALE_ON | OBJ_MODE(0) | OBJ_16_COLOR | ATTR0_SQUARE;
	_attributeObj->attr1 = 112 | ATTR1_ROTDATA(entityNum) | ATTR1_SIZE_16;
	_attributeObj->attr2 = 0 | OBJ_PRIORITY(0) | OBJ_PALETTE(0);
	
	_scytheOAM = _level->lendOAM();
	_scytheAttributeObj = &(OAM[_scytheOAM]);
	
	_affine = &(((OBJAFFINE*) 0x07000000)[entityNum]);
	short cos = Math::cos(_rot);
	short sin = Math::sin(_rot);
	_affine->pa = cos;
	_affine->pb = sin;
	_affine->pc = -sin;
	_affine->pd = cos;
	
	//Init scythe to player hand with same rotation as player
	_scytheAttributeObj->attr0 = OBJ_ROT_SCALE_ON | OBJ_MODE(0) | OBJ_16_COLOR | ATTR0_SQUARE;
	_scytheAttributeObj->attr1 = ATTR1_ROTDATA(entityNum) | ATTR1_SIZE_16;
	_scytheAttributeObj->attr2 = 4 | OBJ_PRIORITY(0) | OBJ_PALETTE(0);
	
	_scytheAttributeObjATTR0 = _scytheAttributeObj->attr0 & 0xFF00;
	
	_swingAttributeObjATTR[0] = OBJ_ROT_SCALE_ON | OBJ_MODE(0) | OBJ_16_COLOR | ATTR0_SQUARE;
	_swingAttributeObjATTR[1] = ATTR1_ROTDATA(entityNum) | ATTR1_SIZE_16;
	_swingAttributeObjATTR[2] = 8 | OBJ_PRIORITY(0) | OBJ_PALETTE(0);
	
	_cursorAttributeObjATTR[0] = OBJ_MODE(0) | OBJ_16_COLOR | ATTR0_SQUARE;
	_cursorAttributeObjATTR[1] = ATTR1_SIZE_16;
	_cursorAttributeObjATTR[2] = OBJ_PRIORITY(2) | OBJ_PALETTE(0);
}

Player::~Player() {
	_level->giveOAMBack(_scytheOAM);
	if (_swingOAM != -1) _level->giveOAMBack(_swingOAM);
}

void Player::BButton() {
	if (!(REG_KEYINPUT & KEY_B)) {
		//B button is pressed
		if (!_lastB) {
			//B button was not pressed last frame (rising edge)
			_level->freeze();
			
			_cursorOAM = _level->lendOAM();
			_cursorAttributeObj = &(OAM[_cursorOAM]);
			_cursorAttributeObj->attr0 = _cursorAttributeObjATTR[0] | 72;
			_cursorAttributeObj->attr1 = _cursorAttributeObjATTR[1] | 112;
			_cursorAttributeObj->attr2 = _cursorAttributeObjATTR[2] | (12 + (_cursorSelect << 2));
			
			//Reset cursor to middle of screen
			cursorX = cursorY = 0;
		}
		
		//Move cursor
		if (~REG_KEYINPUT & DPAD) {
			if (!(REG_KEYINPUT & KEY_RIGHT)) cursorX += PLAYER_CSR_SPEED; //RIGHT
			if (!(REG_KEYINPUT & KEY_LEFT))  cursorX -= PLAYER_CSR_SPEED; //LEFT
			if (!(REG_KEYINPUT & KEY_DOWN))  cursorY += PLAYER_CSR_SPEED; //DOWN
			if (!(REG_KEYINPUT & KEY_UP))    cursorY -= PLAYER_CSR_SPEED; //UP

			_cursorAttributeObj->attr0 = _cursorAttributeObjATTR[0] | (72 + cursorY);
			_cursorAttributeObj->attr1 = _cursorAttributeObjATTR[1] | (112 + cursorX);
		}

		//Change cursor type
		if ((~REG_KEYINPUT & (KEY_L | KEY_R)) && !_lastLR) {
			_cursorSelect = !_cursorSelect;
			_cursorAttributeObj->attr2 = _cursorAttributeObjATTR[2] | (12 + (_cursorSelect << 2));

			if (!_cursorSelect) {
				setColorToPaletteMem(OBJPalette0[1][9], 0, 9);
			}
		}

		//Cycle color when cursor is set to teleport
		*((vu8*) 0x02000100) = _cursorTime;
		if (_cursorSelect) {
			_cursorTime--;
			if ((_cursorTime >> 3) > 5) _cursorTime = 5 << 3;

			loadCycleColorToPaletteMem(teleportColorPalette, 5, 0, 9, _cursorTime >> 3);
		}

		_lastLR = (~REG_KEYINPUT & (KEY_L | KEY_R)) > 0;
		
	} else if (_lastB) {
		//B button is not pressed, but it was pressed last frame (falling edge)
		//Unfreeze game
		_level->unfreeze();
		
		//Unload cursor object
		_level->giveOAMBack(_cursorOAM);
		_cursorOAM = -1;
		
		//Check if entity is inside cursor range
		std::vector<Entity*>* entities = _level->getEntitiesInside(((u16)(x >> 16)) + cursorX, ((u16) (y >> 16)) + cursorY, 16, 16);
		
		if (_cursorSelect) {
			//Teleport
			for (u8 i = 0; i < entities->size(); i++) {
				Entity* e = (*entities)[i];
				if (e->teleport()) {
					//teleport player to entity
					x = e->x;
					y = e->y;
					
					//Move camera to new position
					refreshLevel(_level->getLevel(), e->x >> 16, e->y >> 16);
					
					break;
				}
			}
		} else {
			//Mind control
			for (u8 i = 0; i < entities->size(); i++) {
				Entity* e = (*entities)[i];
				if (e->takeOver()) {
					//Entity can be taken over
					_mindControl = e;

					break;
				}
			}
		}
		
		delete entities;
	}
	
	_lastB = !(REG_KEYINPUT & KEY_B);
}

void Player::update() {
	if (_mindControl) {
		//DPAD
		if (REG_KEYINPUT ^ DPAD) {
			_mindControl->move((REG_KEYINPUT & KEY_RIGHT) ? ((REG_KEYINPUT & KEY_LEFT) ? 0 : -PLAYER_MOV_SPEED) : PLAYER_MOV_SPEED, (REG_KEYINPUT & KEY_DOWN) ? ((REG_KEYINPUT & KEY_UP) ? 0 : -PLAYER_MOV_SPEED) : PLAYER_MOV_SPEED);
		}

		//Update player position
		short sx = (x >> 16) - 8 - _level->getX();
		short sy = (y >> 16) - 8 - _level->getY();
		
		if (sx < -16 || sy < -16 || sx >= SCREEN_WIDTH + 16 || sy >= SCREEN_HEIGHT + 16) {
			_attributeObj->attr0 = (-16 & 0x00FF) | (_attributeObj->attr0 & 0xFF00);
			_attributeObj->attr1 = (-16 & 0x01FF) | (_attributeObj->attr1 & 0xFE00);
		} else {
			_attributeObj->attr0 = (sy & 0x00FF) | (_attributeObj->attr0 & 0xFF00);
			_attributeObj->attr1 = (sx & 0x01FF) | (_attributeObj->attr1 & 0xFE00);


			short sin = Math::sin(_rot);
			short cos = Math::cos(_rot);

			//This should be changed, so the scythe cna be thrown
			_scytheAttributeObj->attr0 = _scytheAttributeObjATTR0;
			_scytheAttributeObj->attr0 |= (sy + ((sin >> 7) | (sin < 0 ? 0xFE00 : 0x0000))) & 0x00FF;
			_scytheAttributeObj->attr1 &= ~0x01FF;
			_scytheAttributeObj->attr1 |= (sx + ((cos >> 7) | (cos < 0 ? 0xFE00 : 0x0000))) & 0x01FF;
		}

		//Disable swing effect if player is controlling enemy
		_swingAttributeObj->attr0 = ATTR0_DISABLED;

		//BACK BUTTONS
		if (!(REG_KEYINPUT & KEY_R)) {
			//This should be changed, if player is able to target anything other than enemy
			((Enemy*) _mindControl)->_rot += PLAYER_ROT_SPEED;
			
			if (((Enemy*) _mindControl)->_rot > 359) ((Enemy*) _mindControl)->_rot -= 360;
		} else if (!(REG_KEYINPUT & KEY_L)) {
			((Enemy*) _mindControl)->_rot -= PLAYER_ROT_SPEED;
			
			if (((Enemy*) _mindControl)->_rot > 359) ((Enemy*) _mindControl)->_rot += 360;
		}

		//A BUTTON
		if (!(REG_KEYINPUT & KEY_A)) {
			((Enemy*) _mindControl)->attack();
		}

		//B BUTTON
		if (!(REG_KEYINPUT & KEY_B)) {
			_mindControl->unTakeOver();
		}

		return;
	}

	if (_level->isTimeFrozen()) {
		BButton();
		return;
	}

	short sin = Math::sin(_rot);
	short cos = Math::cos(_rot);
	
	scanKeys();
	
	//DPAD
	if (REG_KEYINPUT ^ DPAD) {
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
		//Give swing sprite back if attack is ready
		if (_swingOAM != 255) {
			_level->giveOAMBack(_swingOAM);
			_swingOAM = -1;
		}
		
		//Falling edge detection
		if (!(REG_KEYINPUT & KEY_A)) {
			if (_throwButtonHoldDown < PLAYER_TRW_BTN_DOWN_TIME) _throwButtonHoldDown++;
		} else {
			if (_lastA) {
				if (_throwButtonHoldDown < PLAYER_TRW_BTN_DOWN_TIME) {
					std::vector<Entity*>* entities = _level->getEntitiesInside(((sin >> 4) | (sin < 0 ? 0xF000 : 0x0000)) + (x >> 16), -((cos >> 4) | (cos < 0 ? 0xF000 : 0x0000)) + (y >> 16), 16, 16);
					
					for (u8 i = 0; i < entities->size(); i++) {
						(*entities)[i]->collideWithScythe();
					}
					
					delete entities;
					
					//Re-enable swing
					_swingCooldown = 0;
					//Lend OAM to swing
					_swingOAM = _level->lendOAM();
					_swingAttributeObj = &(OAM[_swingOAM]);
					_swingAttributeObj->attr0 = _swingAttributeObjATTR[0];
					_swingAttributeObj->attr1 = _swingAttributeObjATTR[1];
					_swingAttributeObj->attr2 = _swingAttributeObjATTR[2];
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
		
		_lastA = !(REG_KEYINPUT & KEY_A);
	}
	
	//B BUTTON
	BButton();
	
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

void Player::targetDead() {
	_mindControl = nullptr;

	_attributeObj->attr0 &= ~0x00FF;
	_attributeObj->attr1 &= ~0x01FF;
	_attributeObj->attr0 |= 72;
	_attributeObj->attr1 |= 112;

	
	refreshLevel(_level->getLevel(), x >> 16, y >> 16);
}