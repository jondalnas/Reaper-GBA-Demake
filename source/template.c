#include "tonc.h"
#include "tonc_types.h"
#include "tonc_memmap.h"
#include "tonc_memdef.h"
#include "tonc_video.h"

int main(void) {
	REG_DISPCNT = DCNT_MODE3 | DCNT_BG2;
	
	for (int i = 0; i < 10; i++) m3_plot(i+10, 10, CLR_RED);
	for (int i = 0; i < 10; i++) m3_plot(i+10, 20, CLR_RED);
	for (int i = 0; i < 10; i++) m3_plot(9, i+10, CLR_RED);
	for (int i = 0; i < 100; i++) m3_plot(21, i+10, CLR_RED);
	
	for (int i = 0; i < 10; i++) m3_plot(i+32, 10, CLR_RED);
	for (int i = 0; i < 10; i++) m3_plot(i+32, 20, CLR_RED);
	for (int i = 0; i < 100; i++) m3_plot(32, i+10, CLR_RED);
	for (int i = 0; i < 10; i++) m3_plot(42, i+10, CLR_RED);
	
	for (int i = 0; i < 10; i++) m3_plot(i+21, 110, CLR_RED);
}


