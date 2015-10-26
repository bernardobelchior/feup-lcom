#include <minix/syslib.h>
#include <minix/drivers.h>
#include "keyboard.h"
#include "timer.h"

int hook_id;

int kb_subscribe_int(void) {

	hook_id = 4;
	int temp = hook_id;
	if (sys_irqsetpolicy(KB_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id) != 0)
		return -1;

	if (sys_irqenable(&hook_id) != 0)
		return -1;

	return temp;
}

int kb_unsubscribe_int(void) {

	if (sys_irqrmpolicy(&hook_id) != 0)
		return -1;

	if (sys_irqdisable(&hook_id) != 0)
		return -1;

	return 0;
}

long kb_int_handler(void) {

	unsigned long stat, word;
	static unsigned long last = 0x00;
	int attempts = 5;
	int i = 0;

	while (i < attempts) {
		i++;
		sys_inb(KB_STATUS, &stat);
		if ((stat & KB_OUTBUF_FULL)
				&& !(stat & (KB_STAT_PARITY | KB_STAT_TIMEOUT))) { //checks if the output buffer is full and there are no errors
			sys_inb(KB_OUT_BUF, &word); //loads word var with the content of the buffer
			if (word == KB_2BYTE_SCODE) {
				last = word;
				return word; //reads the 0xE0 code, which signals a 2byte scancode, and stores it in the static last
			}

			if (last == KB_2BYTE_SCODE) {
				word = (last << 4 | word); // completes the 2 byte scancode
				last = 0x00;
				return word;
			}

			return word;
		}
		tickdelay(micros_to_ticks(DELAY_US));
	}

}

unsigned short capslock = 0;
unsigned short numlock = 0;
unsigned short scrlock = 0;

void kb_toggle_led(unsigned int led) {
	unsigned long stat, msg;
	int i = 0, attempts = 5;
	unsigned short cmd = 0;





	switch (led) {
	case (0):{
		scrlock = abs(scrlock-1);
		break;
	}

	case (1): {
		numlock = abs(numlock-1);
		break;
	}

	case (2): {
		capslock = abs(capslock-1);
		break;
	}

	default: {
		printf("Invalid input\n");
		return;
	}
	}

	cmd = (capslock << 2) | (numlock << 1) | scrlock;

	do {
		sys_outb(KB_IN_BUF, KB_LED_CMD);
		tickdelay(micros_to_ticks(DELAY_US));
		sys_inb(KB_OUT_BUF, &msg);
	} while (msg != ACK);

	do {

		sys_outb(KB_OUT_BUF, cmd);
		tickdelay(micros_to_ticks(DELAY_US));
		sys_inb(KB_OUT_BUF, &msg);
		if(msg == ACK)
			break;

		if(msg == ERROR){
			kb_toggle_led(led);
			break;
		}

	} while (msg == RESEND);


}

