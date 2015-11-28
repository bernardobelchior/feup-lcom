#include "rtc.h"
#include <minix/syslib.h>

int read_from_RTC(unsigned char address, unsigned char *result){
	sys_outb(RTC_ADDR_REG, address);
	sys_inb(RTC_DATA_REG, result);

	return 0;
}

int write_to_RTC(unsigned char address, unsigned char write){
	sys_outb(RTC_ADDR_REG, address);
	sys_outb(RTC_DATA_REG, write);

	return 0;
}
