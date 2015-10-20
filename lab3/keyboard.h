#include <minix/syslib.h>
#include <minix/drivers.h>

#define DELAY_US    20000
#define BIT(n) (0x01<<(n))
#define KB_IRQ 1

/**
 * @brief Subscribes and enables keyboard interrupts
 *
 * @return Returns bit order in interrupt mask; negative value on failure
 */
int kb_subscribe_int(void );

/**
 * @brief Unsubscribes keyboard interrupts
 *
 * @return Return 0 upon success and non-zero otherwise
 */
int kb_unsubscribe_int(void);

/**
 * @brief  keyboard interrupt handler
 *
 * Increments counter
 */
void kb_int_handler();

