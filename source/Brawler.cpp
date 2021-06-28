#include "Brawler.h"

Brawler::Brawler(u32 x, u32 y, Level* level, OBJATTR* attributeObj, u8 entityNum) : Enemy(x, y, 4, level, attributeObj, entityNum) {}

void Brawler::update() {
	Enemy::update();
}