#include "Enemy.h"

class Brawler: public Enemy {
public:
	Brawler(u32 x, u32 y, Level* level, OBJATTR* attributeObj, u8 brawlerOAM, u8 entityNum);
	~Brawler() {}
	
	void update();
};