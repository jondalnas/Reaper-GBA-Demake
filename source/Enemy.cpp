#include "Enemy.h"

#include "Player.h"
#include "FixedPointMath.h"
#include "Level.h"

#define ENEMY_MOV_SPEED (1 << 16 >> 1)

Enemy::Enemy(u32 x, u32 y, u8 radius, Level* level, u8 tile, u8 entityNum) : Entity(x, y, radius, level), _entityNum(entityNum) {
	_attributeObj->attr0 = (x >> 16) | OBJ_ROT_SCALE_ON | OBJ_MODE(0) | OBJ_16_COLOR | ATTR0_SQUARE;
	_attributeObj->attr1 = (y >> 16) | ATTR1_ROTDATA(entityNum) | ATTR1_SIZE_16;
	_attributeObj->attr2 = tile | OBJ_PRIORITY(2) | OBJ_PALETTE(0);
	
	_initialAttribute = *_attributeObj;
	
	_affine = &(((OBJAFFINE*) 0x07000000)[entityNum]);
	_affine->pa = Math::cos(_rot);
	_affine->pb = Math::sin(_rot);
	_affine->pc = -Math::sin(_rot);
	_affine->pd = Math::cos(_rot);

	_level->addedEnemy();
}

void Enemy::update() {
	if (_dead) return;

	Entity::update();

	if (_takenOver) {
		_attributeObj->attr0 = 72  | (_initialAttribute.attr0 & 0xFF00);
		_attributeObj->attr1 = 112 | (_initialAttribute.attr1 & 0xFE00);

		//Update rotation
		u16 cos = Math::cos(_rot);
		u16 sin = Math::sin(_rot);
		_affine->pa = cos;
		_affine->pb = sin;
		_affine->pc = -sin;
		_affine->pd = cos;

		return;
	}

	if (!_noticedPlayer) {
		if (!isLineToEntityBlocked(_level->getPlayer())) {
			_noticedPlayer = 1;

			_target = (Entity*)_level->getPlayer();
		} else if (!isLineToEntityBlocked(_level->getPlayer()->mindControling())) {
			_noticedPlayer = 1;

			_target = (Entity*)_level->getPlayer()->mindControling();
		}
	} else {
		if (_target->dead()) {
			_noticedPlayer = 0;
			_target = nullptr;

			return;
		}

		lookAtTarget();
		goToTarget();
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

void Enemy::lookAtTarget() {
	//Calc look dir
	short xx = (_target->x - x) >> 16;
	short yy = (_target->y - y) >> 16;
	
	_rot = Math::atan2(xx, yy);
}

void Enemy::goToTarget() {
	short xx = (_target->x - x) >> 16;
	short yy = (_target->y - y) >> 16;
	
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

u8 Enemy::teleport() {
	kill();
	
	return 1;
}

u8 Enemy::takeOver() {
	if (_dead) return 0;

	_takenOver = 1;
	
	//Move camera to new position
	refreshLevel(_level->getLevel(), x >> 16, y >> 16);

	return 1;
}

void Enemy::unTakeOver() {
	kill();
}

void Enemy::melee(Entity* e) {
	kill();
}

void Enemy::kill() {
	if (_dead) return;

	_dead = 1;

	if (_takenOver) {
		//This enemy is taken over
		_takenOver = 0;
		_level->getPlayer()->targetDead();
	}
	
	_attributeObj->attr0 = ATTR0_DISABLED;

	_level->killedEnemy();
}

u8 Enemy::collides(Entity* e) {
	if (_dead) return 0;

	if ((Player*) e == _level->getPlayer()) _level->getPlayer()->kill();
	if ((Enemy*) e  == _level->getPlayer()->mindControling()) ((Enemy*) e)->unTakeOver();

	return 1;
}