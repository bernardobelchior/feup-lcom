#include <minix/syslib.h>
#include <minix/drivers.h>
#include "mouse.h"

unsigned int time = 0;

int hook_id;

int write_to_KBC(char destination, unsigned long information){
	unsigned long status;
	sys_inb(KBC_STATUS, &status);

	if(!(status & (KBC_INBUF_FULL | KBC_STAT_PARITY | KBC_STAT_TIMEOUT))){
		unsigned long i = 0;
		sys_outb(destination, information);
		return 1;
	}

	return 0;
}

int read_from_KBC(char origin, unsigned long* information){
	unsigned long status;
	sys_inb(KBC_STATUS, &status);

	if(!(status & (!KBC_OUTBUF_FULL | KBC_STAT_PARITY | KBC_STAT_TIMEOUT))){
		sys_inb(origin, information);
		return 1;
	}

	return 0;
}

int mouse_subscribe_int(void) {

	hook_id = 20;
	int temp = hook_id;
	if (sys_irqsetpolicy(MOUSE_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id) != 0)
		return -1;

	if (sys_irqenable(&hook_id) != 0)
		return -1;

	write_to_KBC(KBC_COMMAND, 0x00000000 | KBC_ENABLE_MOUSE);
	write_to_KBC(KBC_COMMAND, 0x00000000 | WRITE_TO_MOUSE);
	write_to_KBC(KBC_OUT_BUF, 0x00000000 | ENABLE_DATA_PACKETS);

	return temp;
}

int mouse_unsubscribe_int(void) {

	if (sys_irqrmpolicy(&hook_id) != 0)
		return -1;

	if (sys_irqdisable(&hook_id) != 0)
		return -1;

	return 0;
}

void mouse_int_handler(int counter, char packets[]){
	unsigned long info;
	read_from_KBC(KBC_OUT_BUF, &info);

	packets[counter-1] = (char) info;
}



