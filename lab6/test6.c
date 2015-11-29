#include "test6.h"

int test_config(){
	unsigned long reading;
	unsigned char i;
	for(i = 0; i < 10; i++){
		read_from_RTC(i, &reading);
		printf("Register %d: 0x%x\n", i, reading);
	}

	return 0;
}

int test_date(){
	unsigned long hours, minutes, seconds, day_of_the_week, day, month, year;

	read_from_RTC(RTC_SECONDS_REG, &seconds);
	read_from_RTC(RTC_MINUTES_REG, &minutes);
	read_from_RTC(RTC_HOURS_REG, &hours);
	read_from_RTC(RTC_DAY_OF_WEEK_REG, &day_of_the_week);
	read_from_RTC(RTC_DAY_REG, &day);
	read_from_RTC(RTC_MONTH_REG, &month);
	read_from_RTC(RTC_YEAR_REG, &year);

	printf("%x:%x:%x\t", hours, minutes, seconds);

	switch(day_of_the_week){
	case 0x01:
		printf("Sunday");
		break;
	case 2:
		printf("Monday");
		break;
	case 3:
		printf("Tuesday");
		break;
	case 4:
		printf("Wednesday");
		break;
	case 5:
		printf("Thursday");
		break;
	case 6:
		printf("Friday");
		break;
	case 0x07:
		printf("Saturday");
		break;
	}

	//printf("%x", day_of_the_week);//test another day. It is sunday and day_of_the_week has the value of 0.

	printf(", %x/%x/%x", day, month, year);

	return 0;
}

int test_int(){

}
