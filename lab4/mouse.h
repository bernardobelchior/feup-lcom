#ifndef __MOUSE_H
#define __MOUSE_H
#include "i8042.h"

#define MOUSE_RESET 0xFF
#define MOUSE_RESEND 0xFE
#define MOUSE_SET_DEFAULT 0xF6
#define DISABLE_STRM_MODE 0xF5
#define ENABLE_SEND_PCKT 0xF4
#define SET_SAMPLE_RATE 0xF3
#define SET_REMOTE_MODE 0xEA
#define STATUS_REQ 0xE9
#define SET_RES 0xE8
#define SET_ACC_SCALE 0xE7
#define SET_LIN_SCALE 0xE6

/**
 * @brief Write to KBC
 *
 * @param destination Where to write to
 * @param information What to write
 *
 * @return Returns 1 if information was written successfully. Returns 0 otherwise.
 */
int write_to_KBC(char destination, char information);

/**
 * @brief Read from KBC
 *
 * @param origin Where to read from
 * @param information Where to put the read information
 *
 * @return Returns 1 if information was read successfully. Returns 0 otherwise.
 */
int read_from_KBC(char origin, char *information);

/**
 * @brief Subscribes and enables mouse interrupts
 *
 * @return Returns bit order in interrupt mask; negative value on failure
 */
int mouse_subscribe_int(void );

/**
 * @brief Unsubscribes mouse interrupts
 *
 * @return Return 0 upon success and non-zero otherwise
 */
int mouse_unsubscribe_int(void);

/**
 * @brief Mouse interrupt handler
 *
 * @return Returns packets
 */
void mouse_int_handler(int counter, char packets[]);

#endif
