#include "i8254.h"
#include "i8042.h"
#include "fifo.h"
#include <minix/syslib.h>
#include <minix/drivers.h>

/** @defgroup uart uart
 * @{
 * uart
 */

#ifndef UART_H
#define UART_H

static fifo *com1_receive_fifo;
static fifo *com1_transmit_fifo;
static fifo *com2_receive_fifo;
static fifo *com2_transmit_fifo;

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


/**
 * @brief subscribes to the serial port interrupts
 *
 * @param base_addr COM port to subscribe (1 or 2)
 * @ret 0 if successful
 */
int serial_subscribe_int(unsigned short base_addr);

/**
 * @brief unsubscribes serial port interrupts
 *
 * @param base_addr COM port to unsubscribe(1 or 2)
 * @ret 0 if successful
 */
int serial_unsubscribe_int(unsigned short base_addr);

/**
 * @brief checks the origin of the serial port interrupsts and handles them appropriately
 *
 * @param base_addr relevant COM port
 * @param tx 1 if the VM is the transmitter
 * @param rx 1 if the VM is the receiver
 *
 * @ret 0 if sucessful
 */
int serial_int_handler(unsigned short base_addr, char tx, char rx);

/* LCR funcs*/

/**
 * @brief passes the configuration of the LCR to a char
 *
 * @param base_addr relevant COM port
 * @param *st char pointer to store the configuration
 *
 * @ret 0 if successful
 */
int serial_get_conf(unsigned short base_addr, char *st);

/**
 * @brief changes the configuration of a char
 *
 * @param base_addr relevant COM port
 * @param conf desired configuration of the LCR
 *
 * @ret 0 if successful
 */
int serial_set_conf(unsigned short base_addr, unsigned long conf);


/* LSR Funcs */
/**
 * @brief passes the configuration of the LSR to a char
 *
 * @param base_addr relevant COM port
 * @param *st char pointer to store the configuration
 *
 * @ret 0 if successful
 */
int serial_get_lsr(unsigned short base_addr, char *st);

/* IER funcs */

/**
 * @brief passes the configuration of the IER to a char
 *
 * @param base_addr relevant COM port
 * @param *st char pointer to store the configuration
 *
 * @ret 0 if successful
 */
int serial_get_ier(unsigned short base_addr, char *st);

/**
 * @brief checks if the receiver interrupts are enabled
 */
int serial_check_rx(unsigned short base_addr);

/**
 * @brief toggles the receiver interrupts
 */
int serial_toggle_rx(unsigned short base_addr);

/**
 * @brief checks if the transmitter interrupts are enabled
 */
int serial_check_tx(unsigned short base_addr);

/**
 * @brief toggles the transmitter interrupts
 */
int serial_toggle_tx(unsigned short base_addr);

/**
 * @brief checks if the LSR interrupts are enabled
 */
int serial_check_lsr_ints(unsigned short base_addr);

/**
 * @brief toggles the LSR interrupts
 */
int serial_toggle_lsr_ints(unsigned short base_addr);

/*IIR Funcs*/

/**
 * @brief passes the configuration of the IIR to a char
 *
 * @param base_addr relevant COM port
 * @param *st char pointer to store the configuration
 *
 * @ret 0 if successful
 */
int serial_get_iir(unsigned short base_addr, char *st);

/* DL Funcs*/

/**
 * @brief toggles the DLAB
 */
int serial_toggle_dlab(unsigned short base_addr);

/**
 * @checks the state of the DLAB
 */
int serial_check_dlab(unsigned short base_addr);

/**
 * @brief passes the DL LSB to a char
 *
 * @param base_addr relevant COM port
 * @param *st char pointer to store the configuration
 *
 * @ret 0 if successful
 */
int serial_get_dll(unsigned short base_addr, char *st);

/**
 * @brief passes the DL MSB to a char
 *
 * @param base_addr relevant COM port
 * @param *st char pointer to store the configuration
 *
 * @ret 0 if successful
 */
int serial_get_dlm(unsigned short base_addr, char *st);

/**
 * @brief sets a new LSB for the DL
 *
 * @param base_addr relevant COM port
 * @param dll desired DL LSB
 *
 * @ret 0 if successful
 */
int serial_set_dll(unsigned short base_addr, char dll);

/**
 * @brief sets a new MSB for the DL
 *
 * @param base_addr relevant COM port
 * @param dll desired DL MSB
 *
 * @ret 0 if successful
 */
int serial_set_dlm(unsigned short base_addr, char dlm);

/**
 * @brief passes the configuration of the IIR to a char
 *
 * @param base_addr relevant COM port
 * @param *st char pointer to store the configuration
 *
 * @ret 0 if successful
 */
int serial_get_line_status(unsigned short base_addr, char *st);

/* FIFO funcs */

/**
 * @brief enables the UART FIFO
 */
int serial_enable_fifo(unsigned short base_addr,unsigned char trigger_level);

/**
 * @brief puts a char in the UART transmitter FIFO from the app specific code FIFO
 */
int serial_put_in_fifo(unsigned short base_addr, char word);

/**
 * @brief puts a char in the app specific receiver FIFO from the UART receiver FIFO
 */
int serial_get_from_fifo(unsigned short base_addr, char *word);

/**
 * @brief passes the maximum possible amount of chars in the UART transmitter FIFO from the app specific code FIFO
 */
int serial_fill_transmit(unsigned short base_addr);

/**
 * @brief passes the maximum possible amount of chars in the app specific receiver FIFO from the UART receiver FIFO
 */
int serial_clear_receive(unsigned short base_addr);

/**
 * @brief prints the received chars
 */
void print_receiver_fifo(unsigned short base_addr);


#endif
