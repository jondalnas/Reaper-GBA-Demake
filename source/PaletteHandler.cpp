#include "PaletteHandler.h"
#include <gba_video.h>

u16 PaletteHandler::getOBJColor(char palletBank, char pos) {
	return SPRITE_PALETTE[palletBank * 16 + pos];
}

void PaletteHandler::setOBJColor(char palletBank, char pos, u16 col) {
	SPRITE_PALETTE[palletBank * 16 + pos] = col;
}

u16* PaletteHandler::getOBJPalletBank(char palletBank) {
	return &(SPRITE_PALETTE[palletBank * 16]);
}

u16 PaletteHandler::getBGColor(char palletBank, char pos) {
	return BG_PALETTE[palletBank * 16 + pos];
}

void PaletteHandler::setBGColor(char palletBank, char pos, u16 col) {
	BG_PALETTE[palletBank * 16 + pos] = col;
}

u16* PaletteHandler::getBGPalletBank(char palletBank) {
	return &(BG_PALETTE[palletBank * 16]);
}