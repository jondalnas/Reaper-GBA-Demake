#include "Entity.h"

class Player;

class Enemy: public Entity {
public:
	Enemy(u32 x, u32 y, u8 radius, Level* level, u8 tile, u8 entityNum);
	~Enemy() {}

	virtual void update();
	
	void init(u8 entityNum);
	void collideWithScythe();
	u8 collides(Entity* e);
	void kill();
	u8 teleport();
	
protected:
	void lookAtPlayer(Player* p);
	void goToPlayer(Player* p);

	u16 _rot;
	u8 _entityNum;
	
	u8 _noticedPlayer;
	
private:
	u8 _dead = 0;
	OBJATTR _initialAttribute;
	OBJAFFINE* _affine;
};