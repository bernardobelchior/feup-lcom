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

int serial_get_conf(unsigned short base_addr, unsigned char *st) {

	unsigned long conf;

	int ret;
	if (base_addr == 1)
		ret = sys_inb(COM1_BASE_ADDR + UART_LINE_CTRL, &conf);

	else if (base_addr == 2)
		ret = sys_inb(COM2_BASE_ADDR + UART_LINE_CTRL, &conf);

	*st = (unsigned char) conf;

	return ret;
}

int toggle_dlab(unsigned short base_addr) {
	if(base_addr != 1 && base_addr != 2)
		return -1;

	unsigned char lcr;
	unsigned long conf;

	serial_get_conf(base_addr,&lcr);

	printf("Old LCR: 0x%x\n", lcr);

	lcr = lcr ^ BIT(7); //toggles lcr bit 7

	printf("LCR after XOR: 0x%x\n", lcr);

	if (base_addr == 1) {
		sys_outb(COM1_BASE_ADDR + UART_LINE_CTRL, lcr);
	}
	else {
		sys_outb(COM2_BASE_ADDR + UART_LINE_CTRL, lcr);
	}

	serial_get_conf(base_addr, &conf);
	printf("New LCR: 0x%x\n", conf);
}

int set_dlab(unsigned short base_addr, unsigned char bit){
	if(base_addr != 1 && base_addr != 2)
		return -1;

	unsigned char lcr;
	unsigned long conf;

	serial_get_conf(base_addr,&lcr);

	printf("Old LCR: 0x%x\n", lcr);

	lcr = lcr & (bit << 7);

	if (base_addr == 1) {
		sys_outb(COM1_BASE_ADDR + UART_LINE_CTRL, lcr);
		sys_inb(COM1_BASE_ADDR + UART_LINE_CTRL, &conf);
	}
	else {
		sys_outb(COM2_BASE_ADDR + UART_LINE_CTRL, (unsigned long) lcr);
		sys_inb(COM2_BASE_ADDR + UART_LINE_CTRL, &conf);
	}

	//serial_get_conf(base_addr, &conf);
	printf("New LCR: 0x%x\n", conf);
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
