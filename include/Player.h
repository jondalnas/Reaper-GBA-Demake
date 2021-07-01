#pragma once
#include "Entity.h"
#include <gba_sprites.h>

class Player: public Entity {
public:
	Player(u32 x, u32 y, Level* level, OBJATTR* attributeObj, u8 entityNum);
	~Player() {}

	void update();
	
	void init(u8 entityNum);
	
private:
	u16 _rot;
	u8 _entityNum;
	OBJAFFINE* _affine;
	
	void collideWithScythe() {}
};