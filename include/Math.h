#pragma once

#include <gba_types.h>

namespace Math {
	extern const u16 cos90[91];
	extern const u16 atan2LUT[64];

	short cos(u16 deg);
	short sin(u16 deg);

	u16 atan2(short x, short y);
}