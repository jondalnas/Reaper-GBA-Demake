#pragma once
#include "Entity.h"
#include <gba_sprites.h>

class Player: public Entity {
public:
	Player(u32 x, u32 y, Level* level, u8 entityNum);
	~Player();

	void update();

	void targetDead();
	void kill();

	inline Entity* mindControling() {
		return _mindControl;
	}

	u8 dead() {
		return _dead;
	}
	
private:
	u16 _rot = 0;
	u8 _entityNum;
	OBJAFFINE* _affine;
	
	u8 _scytheOAM = -1;
	u8 _swingOAM = -1;
	u8 _cursorOAM = -1;
	
	OBJATTR* _scytheAttributeObj;
	OBJATTR* _swingAttributeObj;
	u16 _scytheAttributeObjATTR0 = 0;
	u16 _swingAttributeObjATTR[3] = {0};
	u8 _swingCooldown = 255;
	u8 _throwButtonHoldDown = 255;
	u8 _throwTime = 255;
	u8 _lastA = 0;
	u8 _lastB = 0;
	u16 _scytheX = 0, _scytheY = 0;
	short _scytheDX = 0, _scytheDY = 0;
	
	short _cursorX = 0, _cursorY = 0;
	OBJATTR* _cursorAttributeObj;
	u16 _cursorAttributeObjATTR[3] = {0};
	u8 _cursorSelect = 0; //0 = mind control, 1 = teleport
	u8 _lastLR = 0;
	u8 _cursorTime = 0;
	Entity* _mindControl = nullptr; //Entity the player is mindcontrolling, nullptr if none
	u8 _teleportCoolDown = 255;
	u8 _mindControlCoolDown = 255;

	u8 _dead = 0;

	void melee(Entity* e);

	void BButton();
};