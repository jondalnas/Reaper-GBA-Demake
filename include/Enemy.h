#include "Entity.h"

class Player;

class Enemy: public Entity {
public:
	Enemy(u32 x, u32 y, u8 radius, Level* level, u8 tile, u8 entityNum);
	~Enemy() {}

	u16 _rot = 0;

	virtual void update();
	
	void init(u8 entityNum);
	void melee(Entity* e);
	u8 collides(Entity* e);
	void kill();
	u8 teleport();
	u8 takeOver();
	void unTakeOver();
	virtual void attack() = 0;
	
protected:
	void lookAtPlayer(Player* p);
	void goToPlayer(Player* p);

	u8 _entityNum;
	
	u8 _noticedPlayer = 0;
	
private:
	u8 _dead = 0;
	OBJATTR _initialAttribute;
	OBJAFFINE* _affine;

	u8 _takenOver = 0;
};