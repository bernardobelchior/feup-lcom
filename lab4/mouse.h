#ifndef __MOUSE_H
#define __MOUSE_H
#include "i8042.h"


/**
 * @brief Write to KBC
 *
 * @param destination Where to write to
 * @param information What to write
 *
 * @return Returns 1 if information was written successfully. Returns 0 otherwise.
 */
int write_to_KBC(char destination, unsigned long information);

/**
 * @brief Read from KBC
 *
 * @param origin Where to read from
 * @param information Where to put the read information
 *
 * @return Returns 1 if information was read successfully. Returns 0 otherwise.
 */
int read_from_KBC(char origin, unsigned long *information);

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
