#include <gba_video.h>
#include <gba_sprites.h>
#include <gba_interrupt.h>

#include "gfx/Tile.h"
#include "gfx/Palette.h"
#include "Entity.h"
#include "Level.h"

//Maybe addressing OAM directly isn't a good idea, instead copy a OBJATTR[] to OAM on every v-blank, so we don't get screen tearing
Level* currLevel;

void VBlank() {
	currLevel->update();
}

int main(void) {
	irqInit();
	irqEnable(IRQ_VBLANK);
	irqSet(IRQ_VBLANK, VBlank);
	
	REG_DISPCNT = MODE_0 | OBJ_ON | OBJ_1D_MAP; //Set to mode 1, enable object layer, set objects to be stored as 1D in VRAM
	
	REG_BG0CNT = BG_SIZE_0 | (0x8 << 8) | BG_16_COLOR | (0x0 << 2) | 0x0; //Background size = 256x256, screen starts at VRAM + 8 * 2kb, color mode = 16x16, character starts at VRAM + 0 * 16kb, priority = 0
	
	loadPalettesToMem();
	
	EntityData_t playerData = {50, 50, EntityTypes::player};
	
	LevelData_t level0Data = {BG0_ON, 1, &playerData, 1, &playerTiles, &level0Tiles, level0ScreenData};
	currLevel = new Level();
	currLevel->init(&level0Data);
	
	while(1);
}