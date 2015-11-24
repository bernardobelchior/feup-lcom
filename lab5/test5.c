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

	vg_update_screen();

	kbd_test_scan(0);

	return vg_exit();
}

int test_line(unsigned short xi, unsigned short yi, unsigned short xf,
		unsigned short yf, unsigned long color) {
	if (vg_init(VBE_VIDEO_MODE) == NULL)
		return 1;

	if(xi > xf && yi > yf){
		unsigned short tmp = xf;
		xf = xi;
		xi = tmp;

		tmp = yf;
		yf = yi;
		yi = tmp;
	}

	if (vg_draw_line(xi, yi, xf, yf, color) != 0) {
		vg_exit();
		return 1;
	}

	vg_update_screen();

	kbd_test_scan(0);

	return vg_exit();
}

int test_xpm(unsigned short xi, unsigned short yi, char *xpm[]) {
	if (vg_init(VBE_VIDEO_MODE) == NULL)
		return 1;

	if (vg_draw_xpm(xi, yi, xpm) != 0) {
		vg_exit();
		return 1;
	}

	vg_update_screen();

	kbd_test_scan(0);

	return vg_exit();
}

int test_move(unsigned short xi, unsigned short yi, char *xpm[],
		unsigned short hor, short delta, unsigned short time) {
	int width, height;
	char* pixmap;
	int ipc_status;
	message msg;
	int irq_set_timer = timer_subscribe_int();
	int irq_set_keyboard = kb_subscribe_int();
	int r;
	unsigned short counter = 0;
	long character;
	float pixmap_speed, next_position;

	if (vg_init(VBE_VIDEO_MODE) == NULL)
		return 1;

	if ((pixmap = (char*) read_xpm(xpm, &width, &height)) == NULL)
		return 1;

	pixmap_speed = (float) (delta) / (time * 60); //TODO encontrar TICKS_PER_SEC; nao existe

	if (irq_set_timer >= 0)
		irq_set_timer = BIT(irq_set_timer);
	else
		irq_set_timer = 0;

	if (irq_set_keyboard >= 0)
		irq_set_keyboard = BIT(irq_set_keyboard);
	else
		irq_set_keyboard = 0;

	next_position = 0;

	while (counter < time && character != ESC_BREAKCODE) { /* You may want to use a different condition */
		/* Get a request message. */
		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & irq_set_timer) { /* subscribed interrupt */
					timed_scan_int_handler(&counter);
					vg_move_pixmap(xi, yi, width, height, pixmap, hor, next_position);
					vg_update_screen();
					next_position += pixmap_speed;
				}
				if (msg.NOTIFY_ARG & irq_set_keyboard) { /* subscribed interrupt */
					character = kb_int_handler();
				}
				break;
			default:
				break; /* no other notifications expected: do nothing */
			}
		} else { /* received a standard message, not a notification */
			/* no standard messages expected: do nothing */
		}
	}

	free(pixmap);
	return vg_exit();
}

int test_controller() {

	return vg_get_controller_info();

}

