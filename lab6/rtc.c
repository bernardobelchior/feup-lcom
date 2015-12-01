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

void change_RTC_to_binary(){
	unsigned long reading;

	read_from_RTC(RTC_REGISTER_B, &reading);
	write_to_RTC(RTC_REGISTER_B, reading | RTC_BINARY);
}

void change_RTC_to_bcd(){
	unsigned long reading;

	read_from_RTC(RTC_REGISTER_B, &reading);
	write_to_RTC(RTC_REGISTER_B, reading & !RTC_BINARY);
}
