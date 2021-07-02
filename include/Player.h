#pragma once
#include "Entity.h"
#include <gba_sprites.h>

class Player: public Entity {
public:
	Player(u32 x, u32 y, Level* level, OBJATTR* attributeObj, u8 playerOAM, OBJATTR* scytheAttributeObj, u8 scytheOAM, OBJATTR* swingAttributeObj, u8 swingOAM, u8 entityNum);
	~Player() {}

	void update();
	
	void init(u8 entityNum);
	
private:
	u16 _rot;
	u8 _entityNum;
	OBJAFFINE* _affine;
	
	u8 _scytheOAM;
	u8 _swingOAM;
	
	OBJATTR* _scytheAttributeObj;
	OBJATTR* _swingAttributeObj;
	u16 _scytheAttributeObjATTR0;
	u16 _swingAttributeObjATTR0;
	u8 _swingCooldown = 255;
	u8 _throwButtonHoldDown = 255;
	u8 _throwTime = 255;
	u8 _lastA;
	u16 _scytheX, _scytheY;
	short _scytheDX, _scytheDY;
	
	void collideWithScythe() {}
};