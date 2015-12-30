#include "i8254.h"
#include "i8042.h"
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

#define UART_DLL 0
#define UART_DLM 1
#define UART_INT_REG 1
#define UART_LINE_CTRL 3
#define UART_LINE_STATUS 5

//IER bits

#define ENABLE_RECEIVED_DATA_INT 		BIT(0)
#define	ENABLE_TRANSMITTER_EMPTY_INT 	BIT(1)
#define	ENABLE_RECEIVER_LINE_STATUS_INT BIT(2)

int serial_subscribe_int(unsigned short base_addr);
int serial_get_conf(unsigned short base_addr, char *st);
int serial_get_ier(unsigned short base_addr, char *st);
int serial_get_dll(unsigned short base_addr, char *st);
int serial_get_dlm(unsigned short base_addr, char *st);
int serial_unsubscribe_int();
int serial_get_line_status(unsigned short base_addr, char *st);
//int put_word

#endif
