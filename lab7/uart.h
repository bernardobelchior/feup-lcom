#include "i8254.h"
#include "i8042.h"
#include "fifo.h"
#include <minix/syslib.h>
#include <minix/drivers.h>

#ifndef UART_H
#define UART_H

#define UART_FREQ 115200

#define COM1_BASE_ADDR 0x3F8
#define COM2_BASE_ADDR 0x2F8

#define DL 7

#define COM1_IRQ 4
#define COM2_IRQ 3

//UART Offsets

#define UART_DLL 				0 		//With DLAB set to 1
#define UART_DLM 				1 		//With DLAB set to 1

#define UART_RECEIVER_BUFFER		0
#define UART_TRANSMITTER_HOLDER		0
#define UART_INT_REG 				1
#define UART_FIFO_CTRL				2
#define UART_IIR					2
#define UART_LINE_CTRL 				3
#define UART_LINE_STATUS 			5

//IER bits

#define IER_ENABLE_RX							BIT(0)
#define	IER_ENABLE_TX				 			BIT(1)
#define	IER_ENABLE_RECEIVER_LINE_STATUS_INT 	BIT(2)

//FIFO Control Bits

#define FIFO_ENABLE 			BIT(0)
#define FIFO_CLEAR_RECEIVER 	BIT(1)
#define FIFO_CLEAR_TRANSMIT 	BIT(2)

//LSR Bits

#define LSR_RECEIVER_READY 	BIT(0)
#define LSR_OVERRUN_ERROR	BIT(1)
#define LSR_PARITY_ERROR	BIT(2)
#define LSR_FRAMING_ERROR	BIT(3)
#define LSR_THR_EMPTY		BIT(5)



int serial_subscribe_int(unsigned short base_addr);
int serial_unsubscribe_int(unsigned short base_addr, int hook_id);
int serial_int_handler(unsigned short base_addr);

/* LCR funcs*/
int serial_get_conf(unsigned short base_addr, char *st);
int serial_set_conf(unsigned short base_addr, unsigned long conf);


/* LSR Funcs */
int serial_get_lsr(unsigned short base_addr, char *st);

/* IER funcs */
int serial_get_ier(unsigned short base_addr, char *st);

int serial_check_rx(unsigned short base_addr);
int serial_toggle_rx(unsigned short base_addr);

int serial_check_tx(unsigned short base_addr);
int serial_toggle_tx(unsigned short base_addr);

/*IIR Funcs*/
int serial_get_iir(unsigned short base_addr, char *st);

/* DL Funcs*/
int serial_toggle_dlab(unsigned short base_addr);
int serial_check_dlab(unsigned short base_addr);
int serial_get_dll(unsigned short base_addr, char *st);
int serial_get_dlm(unsigned short base_addr, char *st);
int serial_set_dll(unsigned short base_addr, char dll);
int serial_set_dlm(unsigned short base_addr, char dlm);

int serial_get_line_status(unsigned short base_addr, char *st);

/* FIFO funcs */
int serial_enable_fifo(unsigned short base_addr,unsigned char trigger_level);
int serial_put_in_fifo(unsigned short base_addr, char word);
int serial_get_from_fifo(unsigned short base_addr, char *word);
int serial_fill_transmit(unsigned short base_addr);
int serial_clear_receive(unsigned short base_addr);



#endif
