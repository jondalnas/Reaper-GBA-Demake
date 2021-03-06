#include "FixedPointMath.h"

const u16 Math::cos90[91] = {0x0100, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FE, 0x00FE, 0x00FD, 0x00FC,
				 0x00FC, 0x00FB, 0x00FA, 0x00F9, 0x00F8, 0x00F7, 0x00F6, 0x00F4, 0x00F3, 0x00F2,
				 0x00F0, 0x00EE, 0x00ED, 0x00EB, 0x00E9, 0x00E8, 0x00E6, 0x00E4, 0x00E2, 0x00DF,
				 0x00FF, 0x00DB, 0x00D9, 0x00D6, 0x00D4, 0x00D1, 0x00CF, 0x00CC, 0x00C9, 0x00C6,
				 0x00C4, 0x00C1, 0x00BE, 0x00BB, 0x00B8, 0x00B5, 0x00B1, 0x00AE, 0x00AB, 0x00A7,
				 0x00A4, 0x00A1, 0x009D, 0x009A, 0x0096, 0x0092, 0x008F, 0x008B, 0x0087, 0x0083,
				 0x0080, 0x007C, 0x0078, 0x0074, 0x0070, 0x006C, 0x0068, 0x0064, 0x005F, 0x005B,
				 0x0057, 0x0053, 0x004F, 0x004A, 0x0046, 0x0042, 0x003D, 0x0039, 0x0035, 0x0030,
				 0x002C, 0x0028, 0x0023, 0x001F, 0x001A, 0x0016, 0x0011, 0x000D, 0x0008, 0x0004, 0x0000};
				 
const u16 Math::atan2LUT[64] = {0x005A, 0x005A, 0x005A, 0x005A, 0x010E, 0x010E, 0x010E, 0x010E,
								0x00B4, 0x0087, 0x0074, 0x006C, 0x00FF, 0x00FB, 0x00F3, 0x00E1, 
								0x00B4, 0x0099, 0x0087, 0x007B, 0x00F3, 0x00EC, 0x00E1, 0x00CE, 
								0x00B4, 0x00A1, 0x0092, 0x0087, 0x00E9, 0x00E1, 0x00D5, 0x00C6, 
								0x0000, 0x000E, 0x001A, 0x0024, 0x013B, 0x0143, 0x014D, 0x0159, 
								0x0000, 0x0012, 0x0021, 0x002D, 0x0132, 0x013B, 0x0146, 0x0155, 
								0x0000, 0x001A, 0x002D, 0x0038, 0x0128, 0x012F, 0x013B, 0x014D, 
								0x0000, 0x002D, 0x003F, 0x0047, 0x011C, 0x0120, 0x0128, 0x013B};

//Only accepts numbers from 0-359
short Math::cos(u16 deg) {
	if (deg < 90)
		return cos90[deg];
	else if (deg < 180)
		return ~cos90[180-deg] + 1;
	else if (deg < 270)
		return ~cos90[deg-180] + 1;
	else
		return cos90[360-deg];
}

//Only accepts numbers from 0-359
short Math::sin(u16 deg) {
	if (deg < 90)
		return cos90[90-deg];
	else if (deg < 180)
		return cos90[deg-90];
	else if (deg < 270)
		return ~cos90[270-deg] + 1;
	else
		return ~cos90[deg-270] + 1;
}

u16 Math::atan2(short x, short y) {
	u8 xn = 0, yn = 0;
	if (x < 0) {
		xn = 1;
		x = -x;
	}
	if (y < 0) {
		yn = 1;
		y = -y;
	}

	//Right shift until only lower three bits are set
	while ((x & ~3) || (y & ~3)) {
		x >>= 1;
		y >>= 1;
	}
	
	if (xn) {
		x = (-x) & 7;
	}
	if (yn) {
		y = (-y) & 7;
	}
	
	return atan2LUT[(y << 3) | x];
}