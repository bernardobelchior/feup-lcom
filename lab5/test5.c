#include "test5.h"

void *test_init(unsigned short mode, unsigned short delay) {
	void *ret;
	vbe_mode_info_t vmi_p;

	if ((ret = vg_init(mode)) == NULL)
		return NULL;

	timer_test_int(delay);

	if (vbe_get_mode_info(mode, &vmi_p) != 0)
		return NULL;

	if (vg_exit() != 0)
		return NULL;

	//test to see if vbe_get_mode_info is working
	printf("X res: %d\nY res: %d\nBits per pixel: %d\nPhysical Address: %x",
			vmi_p.XResolution, vmi_p.YResolution, vmi_p.BitsPerPixel,
			vmi_p.PhysBasePtr);

	return ret;
}

int test_square(unsigned short x, unsigned short y, unsigned short size,
		unsigned long color) {
	if (vg_init(VBE_VIDEO_MODE) == NULL)
		return 1;

	if (vg_draw_frame(x, y, size, size, color) != 0) {
		vg_exit();
		return 1;
	}

	kbd_test_scan(0);

	return vg_exit();
}

int test_line(unsigned short xi, unsigned short yi, unsigned short xf,
		unsigned short yf, unsigned long color) {
	if (vg_init(VBE_VIDEO_MODE) == NULL)
		return 1;

	if (vg_draw_line(xi, yi, xf, yf, color) != 0) {
		vg_exit();
		return 1;
	}

	kbd_test_scan(0);

	return vg_exit();
}

int test_xpm(unsigned short xi, unsigned short yi, char *xpm[]) {
	if (vg_init(VBE_VIDEO_MODE) == NULL)
		return 1;

	if (vg_draw_pixmap(xi, yi, xpm) != 0) {
		vg_exit();
		return 1;
	}

	kbd_test_scan(0);

	return vg_exit();
}

int test_move(unsigned short xi, unsigned short yi, char *xpm[],
		unsigned short hor, short delta, unsigned short time) {

	if (vg_init(VBE_VIDEO_MODE) == NULL)
		return 1;

	if (vg_draw_pixmap(xi, yi, xpm) != 0) {
		vg_exit();
		return 1;
	}

	if(vg_move_pixmap(xi,yi,xpm,hor,delta,time) != 0){
		vg_exit();
		return 1;
	}

	return vg_exit();

}

int test_controller() {

	/* To be completed */

}

