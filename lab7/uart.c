#include "uart.h"

int hook_id;

int serial_subscribe_int(unsigned short base_addr) {

	hook_id = 7;
	int temp = hook_id;

	if (base_addr == 1) {
		if (sys_irqsetpolicy(COM1_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id)
				!= 0)
			return -1;
	}

	else if (base_addr == 2) {
		if (sys_irqsetpolicy(COM2_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id)
				!= 0)
			return -1;
	}

	if (sys_irqenable(&hook_id) != 0)
		return -1;

	return temp;
}

int serial_get_conf(unsigned short base_addr, char *st) {

	unsigned long conf;

	int ret;
	if (base_addr == 1)
		ret = sys_inb(COM1_BASE_ADDR + UART_LINE_CTRL, &conf);

	else if (base_addr == 2)
		ret = sys_inb(COM2_BASE_ADDR + UART_LINE_CTRL, &conf);

	*st = (char) conf;

	return ret;
}

int serial_get_line_status(unsigned short base_addr, char *st) {

	unsigned long conf;

	int ret = 0;

	/*if(base_addr == 1)
	 ret = sys_outb(base_addr + UART_LINE_STATUS, &conf);

	 if(base_addr == 2)
	 ret = sys_outb(base_addr + UART_LINE_STATUS, &conf);

	 *st = (char) conf;*/
	return ret;
}

int toggle_dlab(unsigned short base_addr) {

	char lcr;
	unsigned long input;
	unsigned long conf;

	serial_get_conf(base_addr,&lcr);

	if ((lcr & BIT(7)) >> 7) {
		printf("!!!  %d\n", lcr);
		input = (lcr & (0x07F));
	}

	else {
		printf("adwdaa %d\n", lcr);
		input = (lcr | BIT(DL));
	}


	input = 0|BIT(6);
	printf("%d\n\n", input);
	if (base_addr == 1) {
		 sys_outb(COM1_BASE_ADDR + UART_LINE_CTRL, input);
	}

	if (base_addr == 2) {
		sys_outb(COM1_BASE_ADDR + UART_LINE_CTRL, input);
	}

	sys_inb(COM1_BASE_ADDR + UART_LINE_CTRL, &conf);
	printf("lcr no toggle %d\n", conf);
	//serial_get_conf(base_addr,&lcr); printf("lcr no toggle :\n%d",lcr);

}

int serial_get_ier(unsigned short base_addr, char *st){

	unsigned long conf;
	int ret = 1;

	if(base_addr == 1)
		ret = sys_inb(COM1_BASE_ADDR + UART_INT_REG,&conf);

	else if(base_addr == 2)
		ret = sys_inb(COM2_BASE_ADDR + UART_INT_REG,&conf);

	*st = (char) conf;

	return ret;
}

int serial_get_dll(unsigned short base_addr, char *st) {

	unsigned long conf;
	int ret = 1;

	if(base_addr == 1)
		ret = sys_inb(COM1_BASE_ADDR + UART_DLL,&conf);

	else if(base_addr == 2)
		ret = sys_inb(COM2_BASE_ADDR + UART_DLL,&conf);

	*st = (char) conf;

	return ret;
}

int serial_get_dlm(unsigned short base_addr, char *st){

	unsigned long conf;
	int ret = 1;

	if(base_addr == 1)
		ret = sys_inb(COM1_BASE_ADDR + UART_DLM,&conf);

	else if(base_addr == 2)
		ret = sys_inb(COM2_BASE_ADDR + UART_DLM,&conf);

	*st = (char) conf;

	return ret;

}
