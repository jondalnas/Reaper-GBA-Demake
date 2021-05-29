#pragma once
#include "Entity.h"
#include <gba_sprites.h>

class Player: public Entity {
public:
	Player(unsigned short x, unsigned short y, OBJATTR* attributeObj, u8 entityNum);
	~Player() {}

	void update();
	
	void init(u8 entityNum);	
private:
	u16 _rot;
	u8 _entityNum;
	OBJAFFINE* _affine;
};