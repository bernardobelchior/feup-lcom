#include <minix/syslib.h>
#include <minix/drivers.h>

#define DELAY_US    20000
#define BIT(n) (0x01<<(n))
#define KB_IRQ 1
#define KB_STATUS 0x64
#define KBC_COMMAND 0x64
#define KB_OUT_BUF 0x60
#define KB_INBUF_FULL BIT(1)
#define KB_OUTBUF_FULL BIT(0)
#define KB_STAT_PARITY BIT(7)
#define KB_STAT_TIMEOUT BIT(6)
#define ESC_BREAKCODE 0x81
#define KB_2BYTE_SCODE 0xE0
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
long kb_int_handler(void);

