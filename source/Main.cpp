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
	
	REG_DISPCNT = MODE_0 | OBJ_ON | OBJ_1D_MAP; //Set to mode 1, enable object layer, set objects to be stored as 1D in VRAM
	
	REG_BG0CNT = BG_SIZE_0 | (0x8 << 8) | BG_16_COLOR | (0x0 << 2) | 0x3; //Background size = 256x256, screen starts at VRAM + 8 * 2kb, color mode = 16x16, character starts at VRAM + 0 * 16kb, priority = 0
	REG_BG1CNT = BG_SIZE_0 | (0x9 << 8) | BG_16_COLOR | (0x0 << 2) | 0x3; //Background size = 256x256, screen starts at VRAM + 9 * 2kb, color mode = 16x16, character starts at VRAM + 0 * 16kb, priority = 0
	
	loadPalettesToMem();
	
	EntityData_t playerData = {164 << 16, 328 << 16, EntityTypes::player};
	EntityData_t brawler0Data = {48 << 16, 48 << 16, EntityTypes::brawler};
	EntityData_t brawler1Data = {56 << 16, 296 << 16, EntityTypes::brawler};
	
	const EntityData_t* level0Entities[3] = {&playerData, &brawler0Data, &brawler1Data};
	const tile_t* level0EntityTiles[5] = {&playerTiles, &scytheTiles, &swingTiles, &cursorTiles, &brawlerTiles};
	
	LevelData_t level0Data = {BG0_ON | BG1_ON, level0width, level0height, 3, level0Entities, 5, level0EntityTiles, &level0Tiles, &level0, level0TileFlag};
	currLevel = new Level(&level0Data);
	
	irqInit();
	irqEnable(IRQ_VBLANK);
	irqSet(IRQ_VBLANK, VBlank);
	
	while(1);
}