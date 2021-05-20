#include <tonc_video.h>
#include <tonc_input.h>
#include <tonc_oam.h>

#include "tools.h"

OBJ_ATTR obj_buffer[128];

int main(void) {
	REG_DISPCNT = DCNT_MODE0 | DCNT_BG0 | DCNT_OBJ | DCNT_OBJ_1D; //Set to mode 1, enable background 1, enable object layer, set objects to be stored as 1D in VRAM
	
	REG_BG0CNT = BG_SIZE0 | (0x8 << 8) | BG_8BPP | (0x0 << 2) | 0x0; //Background size = 256x256, screen starts at VRAM + 8 * 2kb, color mode = 256x1, character starts at VRAM + 0 * 16kb, priority = 0
	
	u16 testTilePal[16] = {0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF};
	u32 testTile[8] = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF};
	
	//Same as memcpy(&tile_mem[4][0], testTile, 16);, but this actually works
	for (int i = 0; i < 8; i++) {
		tile_mem[4][0].data[i] = testTile[i];
	}
	
	for (int i = 0; i < 16; i++) {
		pal_obj_mem[i] = testTilePal[i];
	}
	
	oam_init(obj_buffer, 128);
	
	OBJ_ATTR *test = &obj_buffer[0];
	obj_set_attr(test, ATTR0_SQUARE, ATTR1_SIZE_64, ATTR2_PALBANK(0) | 0);
	
	u8 x = 0, y = 0;
	
	obj_set_pos(test, x, y);
	
	while(1) {
		vid_vsync();
		
		//Input
		key_poll();
		x += key_tri_horz();
		y += key_tri_vert();
		
		obj_set_pos(test, x, y);
		
		//Render
		
		//Update OAM
		oam_copy(oam_mem, obj_buffer, 1);
	}
}