#include <minix/drivers.h>


int main(int argc, char **argv) {

	timer_test_config(0);
	timer_test_config(1);
	timer_test_config(2);

	return 0;
}
