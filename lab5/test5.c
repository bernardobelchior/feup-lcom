#include "test5.h"

void *test_init(unsigned short mode, unsigned short delay) {
	void *ret;
	vbe_mode_info_t vmi_p;

	ret = vg_init(mode);
	/*if ((ret = vg_init(mode)) == NULL)
	 return NULL;*/

	timer_test_int(delay);

	//vbe_get_mode_info(mode, &vmi_p);

	if (vg_exit() != 0)
		return NULL;

	//test to see if vbe_get_mode_info is working
	/*printf("X res: %d\nY res: %d\nBits per pixel: %d\nPhysical Address: %x",
			vmi_p.XResolution, vmi_p.YResolution, vmi_p.BitsPerPixel,
			vmi_p.PhysBasePtr);*/

	return ret;
}

int test_square(unsigned short x, unsigned short y, unsigned short size,
		unsigned long color) {
	vg_init(VBE_VIDEO_MODE);

	if (vg_draw_rectangle(x, y, size, size, color) != 0) {
		if (vg_exit() != 0)
			return 1;
		return 1;
	}

	//kbd_test_scan(0);

	vg_exit();
	return 0;
}

int test_line(unsigned short xi, unsigned short yi, unsigned short xf,
		unsigned short yf, unsigned long color) {

	/* To be completed */

}

int test_xpm(unsigned short xi, unsigned short yi, char *xpm[]) {

	/* To be completed */

}

int test_move(unsigned short xi, unsigned short yi, char *xpm[],
		unsigned short hor, short delta, unsigned short time) {

	/* To be completed */

}

int test_controller() {

	/* To be completed */

}

