#pragma once

#include <gba_types.h>

class PaletteHandler {
public:
	//OBJ pallet bank 0 is player sprite
	static u16 getOBJColor(char palletBank, char pos);
	static void setOBJColor(char palletBank, char pos, u16 col);
	static u16* getOBJPalletBank(char palletBank);
	
	//BG pallet bank 0 is floor
	static u16 getBGColor(char palletBank, char pos);
	static void setBGColor(char palletBank, char pos, u16 col);
	static u16* getBGPalletBank(char palletBank);
};