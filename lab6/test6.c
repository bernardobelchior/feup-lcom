#include "test6.h"

int test_config(){
	unsigned long reading;
	unsigned char i;

	change_RTC_to_binary();

	for(i = 0; i < 10; i++){
		read_from_RTC(i, &reading);
		printf("Register %d: 0x%x\n", i, reading);
	}

	return 0;
}

int test_date(){
	unsigned long hours, minutes, seconds, day_of_the_week, day, month, year;

	change_RTC_to_binary();

	read_from_RTC(RTC_SECONDS_REG, &seconds);
	read_from_RTC(RTC_MINUTES_REG, &minutes);
	read_from_RTC(RTC_HOURS_REG, &hours);
	read_from_RTC(RTC_DAY_OF_WEEK_REG, &day_of_the_week);
	read_from_RTC(RTC_DAY_REG, &day);
	read_from_RTC(RTC_MONTH_REG, &month);
	read_from_RTC(RTC_YEAR_REG, &year);

	printf("%d:%d:%d\t", hours, minutes, seconds);

	switch(day_of_the_week){
	case 0:
		printf("Sunday");
		break;
	case 1:
		printf("Monday");
		break;
	case 2:
		printf("Tuesday");
		break;
	case 3:
		printf("Wednesday");
		break;
	case 4:
		printf("Thursday");
		break;
	case 5:
		printf("Friday");
		break;
	case 7:
		printf("Saturday");
		break;
	}

	//printf("%x", day_of_the_week);//test another day. It is sunday and day_of_the_week has the value of 0.

	printf(", %d/%d/%d", day, month, year);

	return 0;
}

int test_int(){
	change_RTC_to_binary();
}
