#include <tonc_types.h>

u8 playerTileSize = 4;
u16 playerPallet[16] = {0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF};
u32 playerTileData[32] = {0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000022, 0x00000222, 0x00111222,
                          0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x22000000, 0x22200000, 0x22211100,
                          0x00111222, 0x00000222, 0x00000022, 0x00000002, 0x00000002, 0x00000000, 0x00000000, 0x00000000,
                          0x22211100, 0x22200000, 0x22000000, 0x20000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000};