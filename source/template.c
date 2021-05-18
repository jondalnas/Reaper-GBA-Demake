#include <tonc_video.h>
#include <tonc_input.h>

int main(void) {
	REG_DISPCNT = DCNT_MODE3 | DCNT_BG2;
	
	u8 x = 0, y = 0;
	
	while(1) {
		vid_vsync();
		
		//Input
		key_poll();
		x += key_tri_horz();
		y += key_tri_vert();
		
		//Render
		m3_plot(x, y, CLR_RED);
	}
}