#include "rtc.h"
#include <minix/drivers.h>
#include <minix/syslib.h>

int can_access_RTC_reg(){
	unsigned long result;

	sys_outb(RTC_ADDR_REG, RTC_REGISTER_A);
	sys_inb(RTC_DATA_REG, &result);

	return !(result & (unsigned long) RTC_UIP);
}

int read_from_RTC(unsigned char address, unsigned long *result){
	while(!can_access_RTC_reg()){	}
	sys_outb(RTC_ADDR_REG, address);
	sys_inb(RTC_DATA_REG, result);

	return 0;
}

int write_to_RTC(unsigned char address, unsigned long write){
	while(!can_access_RTC_reg()){	}
	sys_outb(RTC_ADDR_REG, address);
	sys_outb(RTC_DATA_REG, write);

	return 0;
}

int is_rtc_binary(){
	unsigned long result;
	sys_outb(RTC_ADDR_REG, RTC_REGISTER_B);
	sys_inb(RTC_DATA_REG, &result);

	return (result & RTC_BINARY);
}

unsigned long convert_to_binary(unsigned long bcd){
	return (bcd & 0x0F) + (((bcd & 0x0F0) >> 4) * 10);
}

Date* get_todays_date(){
	Date* date = (Date*) malloc(sizeof(Date));

	read_from_RTC(RTC_DAY_REG, &(date->day));
	read_from_RTC(RTC_MONTH_REG, &(date->month));
	read_from_RTC(RTC_YEAR_REG, &(date->year));

	if(!is_rtc_binary()){
		date->day = convert_to_binary(date->day);
		date->month = convert_to_binary(date->month);
		date->year = convert_to_binary(date->year);
	}

	return date;
}
