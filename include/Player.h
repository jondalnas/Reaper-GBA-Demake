#pragma once
#include "Entity.h"
#include <gba_sprites.h>

class Player: public Entity {
public:
	Player(u32 x, u32 y, Level* level, u8 entityNum);
	~Player();

	void update();
	
	void init(u8 entityNum);
	
private:
	u16 _rot;
	u8 _entityNum;
	OBJAFFINE* _affine;
	
	u8 _scytheOAM = -1;
	u8 _swingOAM = -1;
	u8 _cursorOAM = -1;
	
	OBJATTR* _scytheAttributeObj;
	OBJATTR* _swingAttributeObj;
	u16 _scytheAttributeObjATTR0;
	u16 _swingAttributeObjATTR[3];
	u8 _swingCooldown = 255;
	u8 _throwButtonHoldDown = 255;
	u8 _throwTime = 255;
	u8 _lastA;
	u8 _lastB;
	u16 _scytheX, _scytheY;
	short _scytheDX, _scytheDY;
	
	short cursorX, cursorY;
	OBJATTR* _cursorAttributeObj;
	u16 _cursorAttributeObjATTR[3];
	u8 _cursorSelect; //0 = mind control, 1 = teleport
	u8 _lastLR;
	u8 _cursorTime;
	
	void collideWithScythe() {}
	void BButton();
};