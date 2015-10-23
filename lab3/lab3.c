#include <minix/drivers.h>
#include "test3.h"

static int proc_args(int argc, char *argv[]);
static unsigned long parse_ulong(char *str, int base);
static long parse_long(char *str, int base);
static void print_usage(char *argv[]);

int main(int argc, char **argv) {
	sef_startup();

	kbd_test_scan(0);

	return 0;
}

static void print_usage(char *argv[]) {
  printf("Usage: one of the following:\n"
	 "\t service run %s -args \"test_scan <unsigned int ass>\" \n"
	 "\t service run %s -args \"test_leds <unsigned long array_size> <unsigned int array leds>\" \n"
	 "\t service run %s -args \"test_timed_scan <unsigned int ass>\" \n",
	 argv[0], argv[0], argv[0]);
}

static int proc_args(int argc, char *argv[]) {

  unsigned long freq, time;
  unsigned char conf;

  /* check the function to test: if the first characters match, accept it */
  if (strncmp(argv[1], "test_scan", strlen("test_scan")) == 0) {
	  if( argc != 3 ) {
		  printf("keyboard: wrong no of arguments for test of kbd_test_scan() \n");
		  return 1;
	  }
	  if( (conf = parse_ulong(argv[2], 0)) == ULONG_MAX )
	 		  return 1;
	  printf("keyboard:: kbd_test_scan(%d)\n", conf);
	  timer_display_conf(conf);
	  return 0;
  } else if (strncmp(argv[1], "test_leds", strlen("test_leds")) == 0) {
	  if( argc < 3 || argc > 6 ) {
		  printf("keyboard: wrong no of arguments for test of kbd_test_leds() \n");
		  return 1;
	  }
	  if( (time = parse_ulong(argv[2], 16)) == ULONG_MAX )
		  return 1;
	  printf("keyboard:: kbd_test_leds(%d)\n", time);
	  timer_test_int(time);
	  return 0;
  } else if (strncmp(argv[1], "test_timed_scan", strlen("test_timed_scan")) == 0) {
	  if( argc != 3 ) {
		  printf("keyboard: wrong no of arguments for test of timer_test_square() \n");
		  return 1;
	  }
	  if( (freq = parse_ulong(argv[2], 16)) == ULONG_MAX )
		  return 1;
	  printf("keyboard:: kbd_test_timed_scan(%d)\n", freq);
	  return timer_test_square(freq);
  } else {
	  printf("keyboard: non valid function \"%s\" to test\n", argv[1]);
	  return 1;
  }
}

static unsigned long parse_ulong(char *str, int base) {
  char *endptr;
  unsigned long val;

  val = strtoul(str, &endptr, base);

  if ((errno == ERANGE && val == ULONG_MAX )
	  || (errno != 0 && val == 0)) {
	  perror("strtol");
	  return ULONG_MAX;
  }

  if (endptr == str) {
	  printf("video_txt: parse_ulong: no digits were found in %s \n", str);
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
	  printf("video_txt: parse_long: no digits were found in %s \n", str);
	  return LONG_MAX;
  }

  /* Successful conversion */
  return val;
}

