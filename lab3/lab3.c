#include <minix/drivers.h>
#include "test3.h"

int main(int argc, char **argv) {
	sef_startup();

	kbd_test_scan(0);

	return 0;
}

