#pragma once

#include <gba_types.h>

namespace Math {
	extern const u16 cos90[91];
	extern const u16 atan2LUT[64];

	u16 cos(u16 deg);
	u16 sin(u16 deg);

	u16 atan2(short x, short y);
}