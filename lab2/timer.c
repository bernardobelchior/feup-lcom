#include <minix/syslib.h>
#include <minix/drivers.h>

int timer_set_square(unsigned long timer, unsigned long freq) {

	return 1;
}

int timer_subscribe_int(void ) {

	return 1;
}

int timer_unsubscribe_int() {

	return 1;
}

void timer_int_handler() {

}

int timer_get_conf(unsigned long timer, unsigned char *st) {
	char read = TIMER_RB_CMD | TIMER_RB_SEL(timer);
	char memory;
	unsigned long conf;

	switch(timer){
		case 0:
			memory = TIMER_0;
			break;
		case 1:
			memory = TIMER_1;
			break;
		case 2:
			memory = TIMER_2;
			break;
	}

	sys_outb(TIMER_CTRL, read);
	int ret = sys_outb(memory, &conf);
	*st = (char) conf;
	return ret;
}

int timer_display_conf(unsigned char conf) {
	

	return 1;
}

int timer_test_square(unsigned long freq) {
	
	return 1;
}

int timer_test_int(unsigned long time) {
	
	return 1;
}

int timer_test_config(unsigned long timer) {
	
	return 1;
}
