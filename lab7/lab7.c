#include <minix/drivers.h>
#include "test7.h"

static int proc_args(int argc, char *argv[]);
static unsigned short parse_ushort(char *str, int base);
static long parse_long(char *str, int base);
static unsigned long parse_ulong(char *str, int base);
static void print_usage(char *argv[]);
static long parse_short(char *str, int base);
static unsigned char parse_uchar(char *str, int base);

int main(int argc, char **argv) {
	sef_startup();
	proc_args(argc, argv);
	return 0;
}

static void print_usage(char *argv[]) {
	printf(
			"Usage: one of the following:\n"
			"\t service run %s -args \"conf 1|2 \n"
			"\t service run %s -args \"set 1|2 <bits> <stop> even|odd|none <rate> \"\n"
			"\t service run %s -args \"com 1|2 tx|rx <bits> <stop> even|odd|none <rate> <string>*\"\n",
			argv[0], argv[0], argv[0], argv[0], argv[0], argv[0]);
}

static int proc_args(int argc, char *argv[]) {

	unsigned short base_addr;
	unsigned long bits, stop, parity, rate;
	unsigned char tx;
	int i, stringc = 1;
	char **strings;
	char *temp;

	/* check the function to test: if the first characters match, accept it */
	if (argc == 1) {
		print_usage(argv);
		return 1;
	}

	else if (strncmp(argv[1], "conf", strlen("conf")) == 0) {
		if (argc != 3) {
			printf("VBE: wrong no of arguments for conf() \n");
			return 1;
		}

		if ((base_addr = parse_ushort(argv[2], 16)) == USHRT_MAX)
			return 1;

		printf("lab7:: conf(%d)\n", base_addr);

		ser_test_conf(base_addr);

		return 0;
	}

	else if (strncmp(argv[1], "set", strlen("set")) == 0) {
		if (argc != 7) {
			printf("lab7: wrong no of arguments for set() \n");
			return 1;
		}

		if ((base_addr = parse_ushort(argv[2], 10)) == USHRT_MAX)
			return 1;

		if ((bits = parse_ulong(argv[3], 10)) == ULONG_MAX)
			return 1;

		if ((stop = parse_ulong(argv[4], 10)) == ULONG_MAX)
			return 1;

		if(strncmp(argv[5],"even",strlen("even")) == 0)
			parity = 2;

		else if(strncmp(argv[5], "odd",strlen("odd")) == 0)
			parity = 1;

		else if(strncmp(argv[5],"none",strlen("none")) == 0)
			parity = 0;

		if((rate = parse_ulong(argv[6],10)) == ULONG_MAX)
			return 1;

		printf("lab7::set(%d, %d, %d, %d, %d)\n", base_addr, bits, stop,
				parity, rate);
		return ser_test_set(base_addr, bits, stop, parity, rate);
	}

	else if (strncmp(argv[1], "com", strlen("com")) == 0) {
		if (argc <	 9) {
			printf("lab7::wrong num of args for com() \n");
			return 1;
		}

		if (base_addr = parse_ushort(argv[2], 10) == USHRT_MAX)
			return 1;

		if ((tx = parse_uchar(argv[3],10)) == UCHAR_MAX)
			return 1;

		if((bits = parse_ulong(argv[4],10)) == ULONG_MAX)
			return 1;

		if((stop = parse_ulong(argv[5],10)) == ULONG_MAX)
			return 1;

		if((rate = parse_ulong(argv[6],10)) == ULONG_MAX)
			return 1;

		if(strncmp(argv[7],"none",strlen("even")) == 0)
			parity = 2;

		else if(strncmp(argv[7], "odd",strlen("odd")) == 0)
			parity = 1;

		else if(strncmp(argv[7],"none",strlen("none")) == 0)
			parity = 0;

		strings = (char **)malloc(0);

		for(i = 8; i < argc; i++){

			strings = realloc(strings,stringc * sizeof(char*));
			strings[stringc - 1] =(char *) malloc(sizeof(argv[i]));
			strings[stringc - 1] = argv[i];
			printf("%s ", strings[stringc - 1]);
			stringc++;
		}

		printf("lab7::set(%d, %d, %d, %d, %d, %d, %d\n", base_addr,
				tx, bits, stop, parity, rate, stringc);
		return ser_test_poll(base_addr, tx, bits, stop, parity, rate,
				stringc, strings);
	}

	else {
		printf("lab7: non valid function \"%s\" to test\n", argv[1]);
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
		printf("VBE: parse_ushort: no digits were found in %s \n", str);
		return USHRT_MAX;
	}

	/* Successful conversion */
	return val;
}

static unsigned long parse_ulong(char *str, int base) {
	char *endptr;
	unsigned long val;

	val = strtoul(str, &endptr, base);

	if ((errno == ERANGE && (val == ULONG_MAX || val == 0))
			|| (errno != 0 && val == 0)) {
		perror("strtol");
		return ULONG_MAX;
	}

	if (endptr == str) {
		printf("VBE: parse_long: no digits were found in %s \n", str);
		return ULONG_MAX;
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
		printf("VBE: parse_long: no digits were found in %s \n", str);
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
			|| (errno != 0 && val == 0)
			|| (errno == ERANGE && (val < SHRT_MIN || val > SHRT_MAX))) {
		perror("strtol");
		return SHRT_MAX;
	}

	if (endptr == str) {
		printf("VBE: parse_long: no digits were found in %s \n", str);
		return SHRT_MAX;
	}

	/* Successful conversion */
	return val;
}

static unsigned char parse_uchar(char *str, int base) {
	char *endptr;
	unsigned long val;

	val = strtol(str, &endptr, base);

	if ((errno == ERANGE && (val == UCHAR_MAX || val == 0))
			|| (errno != 0 && val == 0)) {
		perror("strtol");
		return UCHAR_MAX;
	}


	if (endptr == str) {
		printf("lab7: parse_uchar: no digits were found in %s \n", str);
		return UCHAR_MAX;
	}

	/*Sucessful conversion*/
	return val;
}


