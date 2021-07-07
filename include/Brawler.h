#include "Enemy.h"

class Brawler: public Enemy {
public:
	Brawler(u32 x, u32 y, Level* level, u8 entityNum);
	~Brawler() {}
	
	void update();

	void attack();
};