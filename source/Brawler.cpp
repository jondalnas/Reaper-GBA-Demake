#include "Brawler.h"

#include <vector>

#include "Level.h"
#include "FixedPointMath.h"

Brawler::Brawler(u32 x, u32 y, Level* level, u8 entityNum) : Enemy(x, y, 4, level, 20, entityNum) {}

void Brawler::update() {
	Enemy::update();
}

void Brawler::attack() {
	short sin = Math::sin(_rot);
	short cos = Math::cos(_rot);

	std::vector<Entity*>* entities = _level->getEntitiesInside(((sin >> 4) | (sin < 0 ? 0xF000 : 0x0000)) + (x >> 16), -((cos >> 4) | (cos < 0 ? 0xF000 : 0x0000)) + (y >> 16), 16, 16);
	
	for (u8 i = 0; i < entities->size(); i++) {
		if ((*entities)[i] == this) continue;

		(*entities)[i]->collideWithScythe();

		(*((vu8*) 0x02000100))++;
	}
	
	delete entities;
}