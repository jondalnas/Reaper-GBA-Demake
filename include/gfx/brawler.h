#pragma once

#include <gba_types.h>

const u8 brawlerTileSize = 4;
const u32 brawlerTileData[4][8] = {{0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x43000000, 0x43300000, 0x43311100},
								  {0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000034, 0x00000334, 0x00111334},
								  {0x43311100, 0x43300000, 0x43000000, 0x40000000, 0x40000000, 0x00000000, 0x00000000, 0x00000000},
								  {0x00111334, 0x00000334, 0x00000034, 0x00000004, 0x00000004, 0x00000000, 0x00000000, 0x00000000}};