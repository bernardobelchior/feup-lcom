#ifndef __MOUSE_H
#define __MOUSE_H

#define MOUSE_IRQ 12

/**
 * @brief Subscribes and enables mouse interrupts
 *
 * @return Returns bit order in interrupt mask; negative value on failure
 */
int kb_subscribe_int(void );

/**
 * @brief Unsubscribes mouse interrupts
 *
 * @return Return 0 upon success and non-zero otherwise
 */
int kb_unsubscribe_int(void);

int write_to_KBC(char destination, char information);

/**
 * @brief Mouse interrupt handler
 *
 * @return Returns packets
 */
void mouse_int_handler(int counter, char packets[]);

#endif
