#pragma once

#include <gba_types.h>

#define OBJ_BLOCK 4

//First palette array is real colors, second is gray-scale

//(1-2) player, (1,3-4) brawler, (5-7) scythe, (8) swing, (9) cursor, (9-13) teleport
const u16 OBJPalette0[2][16] = {{0x0000, 0x1405, 0x0000, 0x3617, 0x01C0, 0x1D2F, 0x35CE, 0x4231, 0x7FFF, 0x001F, 0x0000, 0x0000, 0x0000, 0x0000, 0x0, 0x0},
								{0x0000, 0x0842, 0x0000, 0x4A52, 0x2108, 0x2D6B, 0x39CE, 0x4631, 0x7FFF, 0x001F, 0x0000, 0x0000, 0x0000, 0x0000, 0x0, 0x0}};

//Color palette to be cycled
const u16 teleportColorPalette[5] = {0x7C14, 0x6C11, 0x5C0E, 0x400A, 0x2806};

//1-2 level0 floor, 3-4 level0 wall, 5 ground, 6 glass
const u16 BGPalette0[2][16] = {{0x0000, 0x7FE0, 0x7C1F, 0x57BF, 0x0000, 0x5AD6, 0x7FB5, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
							   {0x0000, 0x5AD6, 0x35AD, 0x77BD, 0x0000, 0x5AD6, 0x6F7B, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}};

inline void loadPalettesToMem() {
	for (int i = 0; i < 16; i++) {
		SPRITE_PALETTE[i] = OBJPalette0[0][i];
	}
	
	for (int i = 0; i < 16; i++) {
		BG_PALETTE[i] = BGPalette0[0][i];
	}
}

inline void loadGrayscalePalettesToMem() {
	for (int i = 0; i < 16; i++) {
		SPRITE_PALETTE[i] = OBJPalette0[1][i];
	}
	
	for (int i = 0; i < 16; i++) {
		BG_PALETTE[i] = BGPalette0[1][i];
	}
}

inline void setColorToPaletteMem(u16 col, u8 palette, u8 offs) {
	SPRITE_PALETTE[offs + (palette << 4)] = col;
}

inline void loadCycleColorToPaletteMem(const u16* source, u8 numCol, u8 palette, u8 offs, u8 step) {
	for (u8 i = 0; i < numCol; i++) {
		SPRITE_PALETTE[i + offs + (palette << 4)] = source[(i + step) % (numCol)];
	}
}