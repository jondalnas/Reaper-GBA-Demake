#pragma once
#include "Entity.h"
#include <gba_sprites.h>

class Player: public Entity {
public:
	Player(u32 x, u32 y, Level* level, OBJATTR* attributeObj, OBJATTR* scytheAttributeObj, OBJATTR* swingAttributeObj, u8 entityNum);
	~Player() {}

	void update();
	
	void init(u8 entityNum);
	
private:
	u16 _rot;
	u8 _entityNum;
	OBJAFFINE* _affine;
	
	OBJATTR* _scytheAttributeObj;
	OBJATTR* _swingAttributeObj;
	u16 _swingAttributeObjATTR0;
	u8 _swingCooldown;
	
	void collideWithScythe() {}
};