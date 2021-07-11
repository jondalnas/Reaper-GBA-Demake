#include <gba_types.h>

const u8 pressStartTileSize = 8;
const u32 pressStartTileData[8][8] = {{0xEEEEEEEE, 
									   0xFFEEFFFE, 
									   0xEFEFEEFE, 
									   0xFFEEFFFE, 
									   0xFFEEEEFE, 
									   0xEFE00EFE, 
									   0xEFE00EFE, 
									   0xEEE00EEE},
							          {0xEEEEEEEE, 
									   0xEFFFFEEF, 
									   0xEEEEFEFE, 
									   0xE0EFFEEF, 
									   0xE0EEFEEE, 
									   0xEEEEFEEF, 
									   0xEFFFFEFE, 
									   0xEEEEEEEE},
								      {0xEEEEEEEE, 
									   0xFFFEFFFF, 
									   0xEEFEEEEF, 
									   0xFFFEFFFF, 
									   0xEEEEFEEE, 
									   0xEEEEFEEE, 
									   0xFFFEFFFF, 
									   0xEEEEEEEE},
								      {0xEE0000EE, 
									   0xFE0000EF, 
									   0xFE0000EE, 
									   0xFE0000EF, 
									   0xEE0000EF, 
									   0xEE0000EF, 
									   0xFE0000EF, 
									   0xEE0000EE},
							          {0xEEEEEEEE, 
									   0xFFFFEFFF, 
									   0xEFEEEEEE, 
									   0xEFE0EFFF, 
									   0xEFE0EFEE, 
									   0xEFE0EFEE, 
									   0xEFE0EFFF, 
									   0xEEE0EEEE},
								      {0xEEEEEEEE, 
									   0xFEFFFFEF, 
									   0xFEFEEFEE, 
									   0xFEFEEFE0, 
									   0xFEFFFFE0, 
									   0xFEFEEFE0, 
									   0xFEFEEFE0, 
									   0xEEEEEEE0},
								      {0xEEEEEEEE, 
									   0xFFFFEEFF, 
									   0xEFEEEFEE, 
									   0xEFE0EEFF, 
									   0xEFE00EEF, 
									   0xEFE0EEFE, 
									   0xEFE0EFEE, 
									   0xEEE0EEEE},
								      {0x000000EE, 
									   0x000000EF, 
									   0x000000EE, 
									   0x00000000, 
									   0x00000000, 
									   0x00000000, 
									   0x00000000, 
									   0x00000000}};

const u32 youWinTileSize = 5;
const u32 youWinTileData[5][8] = {{0xEEEE0EEE, 
								   0xFEFEEEFE, 
								   0xFEEFEFEE, 
								   0xFEEEFEE0, 
								   0xFE0EFE00, 
								   0xFE0EFE00, 
								   0xFE0EFE00, 
								   0xEE0EEE00},
								  {0xEEEEEEEE, 
								   0xFEEFEFFF, 
								   0xFEEFEFEE, 
								   0xFEEFEFEE, 
								   0xFEEFEFEE, 
								   0xFEEFEFEE, 
								   0xFFFFEFFF, 
								   0xEEEEEEEE},
								  {0xE0EEE00E, 
								   0xE0EFE00E, 
								   0xE0EFE00E, 
								   0xEEEFE00E, 
								   0xEFEFE00E, 
								   0xFEFFE00E, 
								   0xEEEFE00E, 
								   0xE0EEE00E},
								  {0xEEEEEEEE, 
								   0xEFFFFFEF, 
								   0xEEEFEEEF, 
								   0xE0EFE0EF, 
								   0xE0EFE0EF, 
								   0xEEEFEEEF, 
								   0xEFFFFFEF, 
								   0xEEEEEEEE},
								  {0x000EEEEE, 
								   0x000EFEEF, 
								   0x000EFEEF, 
								   0x000EFEFF, 
								   0x000EFFEF, 
								   0x000EFEEF, 
								   0x000EFEEF, 
								   0x000EEEEE}};