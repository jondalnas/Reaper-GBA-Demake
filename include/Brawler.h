#include "Entity.h"

class Brawler: public Entity {
public:
	Brawler(unsigned short x, unsigned short y, Level* level, OBJATTR* attributeObj, u8 entityNum);
	~Brawler() {}

	void update();
	
	void init(u8 entityNum);	
private:
	u16 _rot;
	u8 _entityNum;
	OBJATTR _initialAttribute;
	OBJAFFINE* _affine;
};