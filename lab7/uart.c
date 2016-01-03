#include "uart.h"

int hook_id;
static fifo *com1_receive_fifo;
static fifo *com1_transmit_fifo;
static fifo *com2_receive_fifo;
static fifo *com2_transmit_fifo;

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

	serial_enable_fifo(base_addr,1);

	if(base_addr == 1){
		if((com1_receive_fifo = fifo_init()) == NULL)
			return -1;

		if((com1_transmit_fifo = fifo_init()) == NULL)
			return -1;
	}

	else if(base_addr == 2){
		if((com2_receive_fifo = fifo_init()) == NULL)
			return -1;

		if((com2_transmit_fifo = fifo_init()) == NULL)
			return -1;
	}

	if (sys_irqenable(&hook_id) != 0)
		return -1;

	return temp;
}

int serial_unsubscribe_int(unsigned short base_addr, int hook_id){


}

int serial_int_handler(unsigned short base_addr){

	char iir, int_origin;

	if(serial_get_iir(base_addr, &iir) != OK)
		return 1;

	if(iir & BIT(0))
		return -1;

	int_origin = (iir & (BIT(3) | BIT(2) | BIT(1))) >> 1;

	switch(int_origin){
	case 0:
		break;
	case 1: //Transmiter Empty
		serial_fill_transmit(base_addr);
		break;
	case 2: //Received Data Available
		break;
	case 3: //Line Status
		break;
	case 4: //Character Timeout Indication
		serial_clear_receive(base_addr);
		break;
	}

	return 0;


}

/* LCR functions*/
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

int serial_set_conf(unsigned short base_addr, unsigned long conf){
	int ret;
	if(base_addr == 1)
		ret = sys_outb(COM1_BASE_ADDR + UART_LINE_CTRL, conf);
	else if(base_addr == 2)
		ret = sys_outb(COM2_BASE_ADDR + UART_LINE_CTRL, conf);

	return ret;
}

/* LSR Funcs */
int serial_get_lsr(unsigned short base_addr,char *st){

	unsigned long temp;
	int ret;

	if(base_addr == 1)
		ret = sys_inb(COM1_BASE_ADDR + UART_LINE_STATUS, &temp);

	else if(base_addr == 2)
		ret = sys_inb(COM2_BASE_ADDR + UART_LINE_STATUS, &temp);

	*st = (char) temp;

	return ret;
}


/* IER funcs */
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

int serial_check_rx(unsigned short base_addr){
	char ier;

	if(serial_get_ier(base_addr, &ier) != OK)
		return -1;

	return (ier & IER_ENABLE_RX);
}

int serial_toggle_rx(unsigned short base_addr){

	unsigned long input;
	char ier;
	int ret;

	if(serial_get_ier(base_addr, &ier) != OK)
		return 1;

	input = (unsigned long) (ier ^ IER_ENABLE_RX);

	if(base_addr == 1)
		ret = sys_outb(COM1_BASE_ADDR + UART_INT_REG, input);

	else if(base_addr == 2)
		ret = sys_outb(COM2_BASE_ADDR + UART_INT_REG, input);

	return ret;
}

int serial_check_tx(unsigned short base_addr){
	char ier;

	if(serial_get_ier(base_addr, &ier) != OK)
		return -1;

	return (ier & IER_ENABLE_TX) >> 1;
}

int serial_toggle_tx(unsigned short base_addr){

	unsigned long input;
	char ier;
	int ret;

	if(serial_get_ier(base_addr, &ier) != OK)
		return 1;

	input = (unsigned long) (ier ^ IER_ENABLE_TX);

	if(base_addr == 1)
		ret = sys_outb(COM1_BASE_ADDR + UART_INT_REG, input);

	else if(base_addr == 2)
		ret = sys_outb(COM2_BASE_ADDR + UART_INT_REG, input);

	return ret;
}

/* IIR funcs */
int serial_get_iir(unsigned short base_addr, char *st){
	int ret;
	unsigned long temp;

	if (base_addr == 1)
		ret = sys_inb(COM1_BASE_ADDR + UART_IIR, &temp);
	else if (base_addr == 2)
		ret = sys_inb(COM2_BASE_ADDR + UART_IIR, &temp);

	*st = (char) temp;

	return ret;
}

/* DL funcs */
int serial_check_dlab(unsigned short base_addr){
	char lcr;
	serial_get_conf(base_addr,&lcr);

	return (lcr & BIT(7)) >> 7;
}

int serial_toggle_dlab(unsigned short base_addr) {

	char lcr;
	unsigned long input;
	unsigned long conf;

	serial_get_conf(base_addr,&lcr);

	input = lcr ^ BIT(7);

	if (base_addr == 1) {
		sys_outb(COM1_BASE_ADDR + UART_LINE_CTRL, input);
	}

	if (base_addr == 2) {
		sys_outb(COM1_BASE_ADDR + UART_LINE_CTRL, input);
	}

	sys_inb(COM1_BASE_ADDR + UART_LINE_CTRL, &conf);

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

int serial_set_dll(unsigned short base_addr, char dll){

	int ret;
	unsigned long input = (unsigned long) dll;

	if(!serial_check_dlab(base_addr))
		serial_toggle_dlab(base_addr);

	if(base_addr == 1)
		ret = sys_outb(COM1_BASE_ADDR + UART_DLL, dll);

	else if (base_addr == 2)
		ret = sys_outb(COM2_BASE_ADDR + UART_DLL, dll);

	return ret;

}

int serial_set_dlm(unsigned short base_addr, char dlm){

	int ret;
	unsigned long input;
	input = (unsigned long) (dlm);

	if(!serial_check_dlab(base_addr))
		serial_toggle_dlab(base_addr);

	if(base_addr == 1)
		ret = sys_outb(COM1_BASE_ADDR + UART_DLM, dlm);

	else if (base_addr == 2)
		ret = sys_outb(COM2_BASE_ADDR + UART_DLL, dlm);

	return ret;
}

/* FIFO funcs */
int serial_enable_fifo(unsigned short base_addr, unsigned char trigger_level){

	unsigned long input = FIFO_ENABLE | FIFO_CLEAR_RECEIVER | FIFO_CLEAR_TRANSMIT;
	int ret;

	switch (trigger_level){
	case 1:
		break;
	case 4:
		input |= BIT(6);
		break;
	case 8:
		input |= BIT(7);
		break;
	case 14:
		input |= (BIT(7) | BIT(6));
		break;
	}

	if(base_addr == 1)
		ret = sys_outb(COM1_BASE_ADDR + UART_FIFO_CTRL, input);

	else if(base_addr == 2)
		ret = sys_outb(COM2_BASE_ADDR + UART_FIFO_CTRL, input);

	return ret;

}

int serial_put_in_fifo(unsigned short base_addr, char word){
	unsigned long input = (unsigned long) word;
	int ret;
	if(serial_check_dlab(base_addr))
		serial_toggle_dlab(base_addr);

	if(base_addr == 1)
		ret = sys_outb(COM1_BASE_ADDR + UART_TRANSMITTER_HOLDER, input);

	else if(base_addr == 2)
		ret = sys_outb(COM2_BASE_ADDR + UART_TRANSMITTER_HOLDER, input);

	return ret;
}

int serial_get_from_fifo(unsigned short base_addr, char *word){
	unsigned long hold;

	if(base_addr == 1)
		if(sys_inb(COM1_BASE_ADDR + UART_RECEIVER_BUFFER, &hold) != OK)
			return -1;

	if(base_addr == 2)
		if(sys_inb(COM2_BASE_ADDR + UART_RECEIVER_BUFFER, &hold) != OK)
			return -1;

	*word = (char) hold;

	return 0;
}

int serial_fill_transmit(unsigned short base_addr){

	char lsr;

	if(base_addr == 1){
		while(!fifo_is_empty(com1_transmit_fifo)){

			serial_get_lsr(base_addr, &lsr);
			if(!(lsr & LSR_THR_EMPTY))
				break;

			if(serial_put_in_fifo(base_addr,fifo_top(com1_transmit_fifo)))
				return 1;
			fifo_pop(com1_transmit_fifo);
		}
	}

	else if(base_addr == 2){
		while(!fifo_is_empty(com2_transmit_fifo)){

			serial_get_lsr(base_addr, &lsr);
			if(!(lsr & LSR_THR_EMPTY))
				break;

			if(serial_put_in_fifo(base_addr, fifo_top(com2_transmit_fifo)))
				return 1;
			fifo_pop(com2_transmit_fifo);
		}
	}

	return 0;

}

int serial_clear_receive(unsigned short base_addr){

	char lsr;
	char temp, *word;
	fifo_element *novo;


	serial_get_lsr(base_addr, &lsr);

	while(lsr & LSR_RECEIVER_READY){

		if((lsr & LSR_OVERRUN_ERROR) >> 1){
			printf("\tLSR :: Overrun Error\n");
			return 1;
		}

		if((lsr & LSR_PARITY_ERROR) >> 2){
			printf("\tLSR :: Parity Error\n");
			return 1;
		}

		if((lsr & LSR_FRAMING_ERROR) >> 3){
			printf("\tLSR :: Framing Error\n");
			return 1;
		}

		serial_get_from_fifo(base_addr, &temp);
		novo = new_element(temp);

		if(base_addr == 1)
			fifo_push(com1_receive_fifo,novo);

		else if(base_addr == 2)
			fifo_push(com2_receive_fifo,novo);
	}

	return 0;
}
