#pragma once

#include <gba_types.h>

const u8 playerTileSize = 4;
const u32 playerTileData[4][8] = {{0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x22000000, 0x22200000, 0x22211100},
								  {0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000022, 0x00000222, 0x00111222},
								  {0x22211100, 0x22200000, 0x22000000, 0x20000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000},
								  {0x00111222, 0x00000222, 0x00000022, 0x00000002, 0x00000002, 0x00000000, 0x00000000, 0x00000000}};
								  
const u8 scytheTileSize = 4;
const u32 scytheTileData[4][8] = {{0x00000000, 0x66000000, 0x77600000, 0x67600000, 0x67600000, 0x00660000, 0x00000000, 0x00000000},
								  {0x00006666, 0x00666777, 0x00666666, 0x00605506, 0x00005500, 0x00005500, 0x00005600, 0x00006600},
								  {0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000},
								  {0x00066600, 0x00006600, 0x00066600, 0x00006500, 0x00005500, 0x00005500, 0x00005500, 0x00005500}};
								  
const u8 swingTileSize = 4;
const u32 swingTileData[4][8] = {{0x88880000, 0x88888800, 0x00088880, 0x00000880, 0x00000008, 0x00000000, 0x00000000, 0x00000000},
								 {0x00008888, 0x00008888, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000},
								 {0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000},
								 {0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000}};
								  
const u8 cursorTileSize = 4;
const u32 cursorTileData[4][8] = {{0x99000000, 0x90990000, 0x90909000, 0x09000900, 0x99999990, 0x09000990, 0x00909009, 0x00990009},
								  {0x00000099, 0x00009909, 0x00090909, 0x00900090, 0x09999999, 0x09900090, 0x90090900, 0x90009900},
								  {0x09900909, 0x90090009, 0x90090090, 0x09990090, 0x00099900, 0x90009000, 0x00990000, 0x99000000},
								  {0x90900990, 0x90009009, 0x09009009, 0x09009990, 0x00999000, 0x00090009, 0x00009900, 0x00000099}};