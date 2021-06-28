#include "Entity.h"

class Player;

class Enemy: public Entity {
public:
	Enemy(u32 x, u32 y, u8 radius, Level* level, OBJATTR* attributeObj, u8 entityNum);
	~Enemy() {}

	virtual void update();
	
	void init(u8 entityNum);
	
protected:
	void calcEnemyLookDir(Player* p);
	void goToPlayer(Player* p);

	u16 _rot;
	u8 _entityNum;
	OBJATTR _initialAttribute;
	OBJAFFINE* _affine;
};