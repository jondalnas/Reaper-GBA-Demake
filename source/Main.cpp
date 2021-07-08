#include <gba_video.h>
#include <gba_sprites.h>
#include <gba_interrupt.h>

#include "gfx/Tile.h"
#include "gfx/Palette.h"
#include "gfx/LevelHandler.h"
#include "Entity.h"
#include "Level.h"

//Maybe addressing OAM directly isn't a good idea, instead copy a OBJATTR[] to OAM on every v-blank, so we don't get screen tearing
Level* currLevel;

void reloadLevel() {
	loadPalettesToMem();

	//Delete old level
	delete currLevel;

	//Create new level
	currLevel = new Level(&level0Data);
}

void VBlank() {
	if (currLevel->shouldRestart()) reloadLevel();

	currLevel->update();
}

int main(void) {
	
	REG_DISPCNT = MODE_0 | OBJ_ON | OBJ_1D_MAP; //Set to mode 1, enable object layer, set objects to be stored as 1D in VRAM
	
	REG_BG0CNT = BG_SIZE_0 | (0x8 << 8) | BG_16_COLOR | (0x0 << 2) | 0x3; //Background size = 256x256, screen starts at VRAM + 8 * 2kb, color mode = 16x16, character starts at VRAM + 0 * 16kb, priority = 0
	REG_BG1CNT = BG_SIZE_0 | (0x9 << 8) | BG_16_COLOR | (0x0 << 2) | 0x3; //Background size = 256x256, screen starts at VRAM + 9 * 2kb, color mode = 16x16, character starts at VRAM + 0 * 16kb, priority = 0
	
	reloadLevel();
	
	irqInit();
	irqEnable(IRQ_VBLANK);
	irqSet(IRQ_VBLANK, VBlank);
	
	while(1);
}