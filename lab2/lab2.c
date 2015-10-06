#include <minix/drivers.h>


int main(int argc, char **argv) {
	unsigned char st;
	timer_get_conf(0, &st);
	timer_display_conf(st);

	return 0;
}
