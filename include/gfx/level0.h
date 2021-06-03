#pragma once

#include <gba_types.h>
/*const u32 floorTileData[8] = {0x11111112, 0x11111112, 0x11111112, 0x11111112, 0x11111112, 0x11111112, 0x11111112, 0x22222222};
const u32 wallLRData[8] = {0x00000000, 0x00000000, 0x33333333, 0x44444444, 0x44444444, 0x33333333, 0x00000000, 0x00000000};
const u32 wallUDData[8] = {0x00344300, 0x00344300, 0x00344300, 0x00344300, 0x00344300, 0x00344300, 0x00344300, 0x00344300};*/
extern const u32 level0TileData[7][8];

extern const u16 level0width;
extern const u16 level0height;
extern const u16 level0defaultTile;
extern const u16 level0ScreenData0[47*42];

extern const u16 level0ScreenData1[47*42];

extern const u16* level0ScreenData[2];