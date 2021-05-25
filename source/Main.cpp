#include <gba_video.h>
#include <gba_input.h>
#include <gba_sprites.h>
#include <gba_interrupt.h>

#include "gfx/Tile.h"
#include "Entity.h"
#include "Level.h"

//Maybe addressing OAM directly isn't a good idea, instead copy a OBJATTR[] to OAM on every v-blank, so we don't get screen tearing
Entity* player;

void VBlank() {
	scanKeys();
	if (REG_KEYINPUT & DPAD) {
		player->x += (REG_KEYINPUT & KEY_RIGHT) ? ((REG_KEYINPUT & KEY_LEFT) ? 0 : -1) : 1;
		player->y += (REG_KEYINPUT & KEY_DOWN) ? ((REG_KEYINPUT & KEY_UP) ? 0 : -1) : 1;
	}
	
	player->update();
}

int main(void) {
	irqInit();
	irqEnable(IRQ_VBLANK);
	irqSet(IRQ_VBLANK, VBlank);
	
	REG_DISPCNT = MODE_0 | OBJ_ON | OBJ_1D_MAP; //Set to mode 1, enable object layer, set objects to be stored as 1D in VRAM
	
	REG_BG0CNT = BG_SIZE_0 | (0x8 << 8) | BG_16_COLOR | (0x0 << 2) | 0x0; //Background size = 256x256, screen starts at VRAM + 8 * 2kb, color mode = 16x16, character starts at VRAM + 0 * 16kb, priority = 0
	
	for (int i = 0; i < 16; i++) {
		SPRITE_PALETTE[i] = playerPallet[i];
	}
	
	for (int i = 0; i < 16; i++) {
		BG_PALETTE[i] = floorPallet[i];
	}
	
	EntityData_t playerData = {0, 0, SQUARE, false, false, 0, false, false, 1, false, false, 0, 0, 0, 0};
	
	LevelData_t level0Data = {BG0_ON, 1, &playerData, 1, &playerTiles, &level0Tiles, level0ScreenData};
	Level level0;
	level0.init(&level0Data);
	
	player = level0.getEntity(0);
	
	while(1);
}