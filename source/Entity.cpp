#include "Entity.h"

void Entity::update() {
	_attributeObj->attr0 &= ~0x00ff; //0x00ff = y bitmask
	_attributeObj->attr0 |= y & 0x00ff;
	_attributeObj->attr1 &= ~0x01ff; //0x01ff = x bitmask
	_attributeObj->attr1 |= x & 0x01ff;
}

void Entity::init(u8 shape, bool colorMode, bool mosaic, u8 OBJMode, bool doubleMode, bool rotScale, u8 size, bool flipH, bool flipV, u8 rotScaleParam, u8 paleteBank, u8 priority, u8 characterName) {
	_attributeObj->attr0 = y | (rotScale << 8) | (doubleMode << 9) | ((OBJMode & 3) << 10) | (mosaic << 12) | (colorMode << 13) | ((shape & 3) << 14);
	_attributeObj->attr1 = x | ((rotScaleParam & 31) << 9) | (flipH << 12) | (flipH << 13) | ((size & 3) << 14);
	_attributeObj->attr2 = characterName | OBJ_PRIORITY(priority & 3) | OBJ_PALETTE(paleteBank & 15);
}