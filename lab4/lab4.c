#include "test4.h"
#include <minix/drivers.h>

static int proc_args(int argc, char *argv[]);
static unsigned short parse_ushort(char *str, int base);
static long parse_long(char *str, int base);
static void print_usage(char *argv[]);
static long parse_short(char *str, int base);

int main(int argc, char **argv) {
	sef_startup();
	proc_args(argc, argv);
	return 0;
}

static void print_usage(char *argv[]) {
	printf(
			"Usage: one of the following:\n"
					"\t service run %s -args \"test_packet <unsigned short cnt>\" \n"
					"\t service run %s -args \"test_async <unsigned short idle_time>\" \n"
					"\t service run %s -args \"test_config \" \n"
					"\t service run %s -args \"test_gesture <short length> <unsigned short tolerance>\" \n",
			argv[0], argv[0], argv[0], argv[0]);
}

static int proc_args(int argc, char *argv[]) {

	unsigned short cnt, tolerance, idle_time;
	short length;

	/* check the function to test: if the first characters match, accept it */
	if (argc == 1) {
		print_usage(argv);
		return 1;
	}

	else if (strncmp(argv[1], "test_packet", strlen("test_packet")) == 0) {
		if (argc != 3) {
			printf("keyboard: wrong no of arguments for test_packet() \n");
			return 1;
		}

		if ((cnt = parse_ushort(argv[2], 10)) == USHRT_MAX)
			return 1;

		printf("mouse:: test_packet(%d)\n", cnt);
	return test_packet(cnt);

}

else if (strncmp(argv[1], "test_async", strlen("test_async")) == 0) {
	if (argc != 3) {
		printf("mouse: wrong no of arguments for test_async() \n");
		return 1;
	}
	if ((idle_time = parse_ushort(argv[2], 10)) == USHRT_MAX)
		return 1;

	printf("mouse::test_async(%d)\n",idle_time);
	return test_async(idle_time);

}

else if (strncmp(argv[1], "test_config", strlen("test_config")) == 0) {
	if (argc != 1) {
		printf("keyboard: wrong no of arguments for test of test_config \n");
		return 1;
	}
	printf("mouse::test_config()\n");
	return test_config();

}

else if (strncmp(argv[1], "test_gesture", strlen("test_gesture")) == 0) {
	if (argc != 3) {
		printf("keyboard: wrong no of arguments for test of test_gesture \n");
		return 1;

	}

	if ((length = parse_short(argv[2], 10)) == SHRT_MAX)
		return 1;

	if ((tolerance = parse_ushort(argv[3], 10)) == USHRT_MAX)
		return 1;

	printf("mouse::test_gesture(%d,%d)\n", length, tolerance);
	return test_gesture(length,tolerance);

} else {
	printf("keyboard: non valid function \"%s\" to test\n", argv[1]);
	return 1;
}
}

static unsigned short parse_ushort(char *str, int base) {
char *endptr;
unsigned long val;

val = (unsigned short) strtoul(str, &endptr, base);

if ((errno == ERANGE && val == USHRT_MAX) || (errno != 0 && val == 0)) {
	perror("strtol");
	return USHRT_MAX;
}

if (endptr == str) {
	printf("video_txt: parse_ushort: no digits were found in %s \n", str);
	return USHRT_MAX;
}

/* Successful conversion */
return val;
}

static long parse_long(char *str, int base) {
char *endptr;
unsigned long val;

val = strtol(str, &endptr, base);

if ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN))
		|| (errno != 0 && val == 0)) {
	perror("strtol");
	return LONG_MAX;
}

if (endptr == str) {
	printf("video_txt: parse_long: no digits were found in %s \n", str);
	return LONG_MAX;
}

/* Successful conversion */
return val;
}

static long parse_short(char *str, int base) {
char *endptr;
unsigned long val;

val = strtol(str, &endptr, base);

if ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN))
		|| (errno != 0 && val == 0) || (val > SHRT_MAX || val < SHRT_MIN)) {
	perror("strtol");
	return SHRT_MAX;
}

if (endptr == str) {
	printf("video_txt: parse_long: no digits were found in %s \n", str);
	return SHRT_MAX;
}

/* Successful conversion */
return val;
}

