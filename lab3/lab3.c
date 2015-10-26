#include <minix/drivers.h>
#include "test3.h"


static int proc_args(int argc, char *argv[]);
static unsigned short parse_ushort(char *str, int base);
static long parse_long(char *str, int base);
static void print_usage(char *argv[]);

int main(int argc, char **argv) {
	sef_startup();

	proc_args(argc,argv);

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

  unsigned short ass, n, time;
  unsigned char conf;

  /* check the function to test: if the first characters match, accept it */
  if(argc == 1){
	  print_usage(argv);
	  return 1;
  }

  else if (strncmp(argv[1], "test_scan", strlen("test_scan")) == 0) {
	  if( argc != 3 ) {
		  printf("keyboard: wrong no of arguments for test of kbd_test_scan() \n");
		  return 1;
	  }

	  if( (ass = parse_ushort(argv[2], 10)) == USHRT_MAX )
		  return 1;

	  printf("keyboard:: kbd_test_scan(%d)\n", ass);
	  kbd_test_scan(ass);
	  return 0;

  } else if (strncmp(argv[1], "test_leds", strlen("test_leds")) == 0) {
	  if( argc < 4) {
		  printf("keyboard: wrong no of arguments for test of kbd_test_leds() \n");
		  return 1;
	  }
	  if( (n = parse_ushort(argv[2], 10)) == USHRT_MAX )
		  return 1;

	  unsigned short i=0, toggle[n];

	  for(;i<n;i++){
		  if(parse_ushort(argv[3+i],10) == USHRT_MAX)
			  break;
		  toggle[i]=parse_ushort(argv[3+i],10);
	  }
	  printf("keyboard:: kbd_test_leds\n");
	  kbd_test_leds(n,toggle);
	  return 0;


  } else if (strncmp(argv[1], "test_timed_scan", strlen("test_timed_scan")) == 0) {
	  if( argc != 3 ) {
		  printf("keyboard: wrong no of arguments for test of test_timed_scan \n");
		  return 1;
	  }
	  if( (time = parse_ushort(argv[2], 16)) == USHRT_MAX )
		  return 1;
	  printf("keyboard:: kbd_test_timed_scan(%d)\n", time);
	  return kbd_test_timed_scan(time);
  } else {
	  printf("keyboard: non valid function \"%s\" to test\n", argv[1]);
	  return 1;
  }
}

static unsigned short parse_ushort(char *str, int base) {
  char *endptr;
  unsigned long val;

  val =(unsigned short) strtoul(str, &endptr, base);

  if ((errno == ERANGE && val == USHRT_MAX )
	  || (errno != 0 && val == 0)) {
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

