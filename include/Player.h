#pragma once
#include "Entity.h"

class Player: public Entity {
public:
	Player(unsigned short x, unsigned short y, OBJATTR* attributeObj, u8 entityNum);
	~Player() {}

	void update();
	
	void init(u8 entityNum);	
private:
	u8 rot;
};