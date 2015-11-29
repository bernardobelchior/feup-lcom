#include "test6.h"

static int proc_args(int argc, char *argv[]);

int main(int argc, char **argv) {
	sef_startup();
	proc_args(argc, argv);
	return 0;
}

static void print_usage(char *argv[]) {
	printf(
			"Usage: one of the following:\n"
			"\t service run %s -args \"test_config\" \n"
			"\t service run %s -args \"test_date\" \n"
			"\t service run %s -args \"test_int\" \n",
			argv[0], argv[0], argv[0]);
}

static int proc_args(int argc, char *argv[]) {

	/* check the function to test: if the first characters match, accept it */
	if (argc == 1) {
		print_usage(argv);
		return 1;
	}

	else if (strncmp(argv[1], "test_config", strlen("test_config")) == 0) {
		if (argc != 2) {
			printf("RTC: wrong no of arguments for test_config() \n");
			return 1;
		}

		printf("RTC::test_config()\n");
		return test_config();
	}

	else if (strncmp(argv[1], "test_date", strlen("test_date")) == 0) {
		if (argc != 2) {
			printf("RTC: wrong no of arguments for test_date() \n");
			return 1;
		}

		printf("RTC::test_date()\n");
		return test_date();
	}

	else if (strncmp(argv[1], "test_int", strlen("test_int")) == 0) {
		if (argc != 2) {
			printf("RTC: wrong no of arguments for test of test_int() \n");
			return 1;
		}

		printf("RTC::test_int()\n");
		return test_int();
	}
	else {
		printf("RTC: non valid function \"%s\" to test\n", argv[1]);
		return 1;
	}
}
