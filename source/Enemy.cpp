#include "Enemy.h"

#include "Player.h"
#include "Math.h"
#include "Level.h"

#define ENEMY_MOV_SPEED (1 << 16 >> 1)

Enemy::Enemy(u32 x, u32 y, u8 radius, Level* level, OBJATTR* attributeObj, u8 entityNum) : Entity(x, y, radius, level, attributeObj), _entityNum(entityNum) {
	_attributeObj->attr0 = (x >> 16) | OBJ_ROT_SCALE_ON | OBJ_MODE(0) | OBJ_16_COLOR | ATTR0_SQUARE;
	_attributeObj->attr1 = (y >> 16) | ATTR1_ROTDATA(entityNum) | ATTR1_SIZE_16;
	_attributeObj->attr2 = 4 | OBJ_PRIORITY(0) | OBJ_PALETTE(0);
	
	_initialAttribute = *_attributeObj;
	
	_affine = &(((OBJAFFINE*) 0x07000000)[entityNum]);
	_affine->pa = Math::cos(_rot);
	_affine->pb = Math::sin(_rot);
	_affine->pc = -Math::sin(_rot);
	_affine->pd = Math::cos(_rot);
}

void Enemy::update() {
	if (_dead) return;

	Entity::update();

	if (!isLineToEntityBlocked(_level->getPlayer())) {
		_noticedPlayer = 1;
	}
	
	if (_noticedPlayer) {
		lookAtPlayer(_level->getPlayer());
		goToPlayer(_level->getPlayer());
	}

	//Update entity parts
	u16 cos = Math::cos(_rot);
	u16 sin = Math::sin(_rot);
	_affine->pa = cos;
	_affine->pb = sin;
	_affine->pc = -sin;
	_affine->pd = cos;
	
	short sx = (x >> 16) - 8 - _level->getX();
	short sy = (y >> 16) - 8 - _level->getY();
	
	if (sx < -16 || sy < -16 || sx >= SCREEN_WIDTH + 16 || sy >= SCREEN_HEIGHT + 16) {
		_attributeObj->attr0 = ATTR0_DISABLED;
	} else {
		_attributeObj->attr0 = (sy & 0x00FF) | (_initialAttribute.attr0 & 0xFF00);
		_attributeObj->attr1 = (sx & 0x01FF) | (_initialAttribute.attr1 & 0xFE00);
	}
}

void Enemy::lookAtPlayer(Player* p) {
	//Calc look dir
	short xx = (p->x - x) >> 16;
	short yy = (p->y - y) >> 16;
	
	_rot = Math::atan2(xx, yy);
}

void Enemy::goToPlayer(Player* p) {
	short xx = (p->x - x) >> 16;
	short yy = (p->y - y) >> 16;
	
	if (xx == 0) {
		if (yy < 0) {
			move(0, -ENEMY_MOV_SPEED);
		} else {
			move(0, ENEMY_MOV_SPEED);
		}
	} else if (yy == 0) {
		if (xx < 0) {
			move(-ENEMY_MOV_SPEED, 0);
		} else {
			move(ENEMY_MOV_SPEED, 0);
		}
	} else if (xx < 0) {
		if (yy < 0) {
			move(-ENEMY_MOV_SPEED, -ENEMY_MOV_SPEED);
		} else {
			move(-ENEMY_MOV_SPEED, ENEMY_MOV_SPEED);
		}
	} else {
		if (yy < 0) {
			move(ENEMY_MOV_SPEED, -ENEMY_MOV_SPEED);
		} else {
			move(ENEMY_MOV_SPEED, ENEMY_MOV_SPEED);
		}
	}
}

void Enemy::collideWithScythe() {
	kill();
}

void Enemy::kill() {
	_dead = 1;
	
	_attributeObj->attr0 = ATTR0_DISABLED;
}

u8 Enemy::collides(Entity* e) {
	if (_dead) return 0;

	return 1;
}