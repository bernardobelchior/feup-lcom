#include "test6.h"

int test_config(){
	unsigned long reading;
	unsigned char i;

	if(is_rtc_binary())
		printf("Registers are in binary:\n");
	else
		printf("Registers are in BCD:\n");

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

	if(!is_rtc_binary()){
		hours = convert_to_binary(hours);
		minutes = convert_to_binary(minutes);
		seconds = convert_to_binary(seconds);
		day = convert_to_binary(day);
		month = convert_to_binary(month);
		year = convert_to_binary(year);
	}

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
	case 6:
		printf("Saturday");
		break;
	}

	printf(", %d/%d/%d", day, month, year);

	return 0;
}

int test_int(){

}
