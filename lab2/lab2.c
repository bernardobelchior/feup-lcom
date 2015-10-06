#include <minix/drivers.h>


int main(int argc, char **argv) {

	sef_startup();

	timer_test_config(0);
	timer_test_config(0);
	timer_test_config(0);

	return 0;
}
