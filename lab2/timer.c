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
	char read = 0xC0;
	char memory = 0x40;
	unsigned long conf;

	swtich(timer){
		case 0:
			read += 2;
			break;
		case 1:
			memory += 1;
			read += 4;
			break;
		case 2:
			memory += 2;
			read += 8;
			break;
	}

	sys_outb(0x43, read);
	sys_outb(memory, &conf);
	
	*st = conf;

	return 1;
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
