#ifndef __TIMER_H
#define __TIMER_H

/** @defgroup timer timer
 * @{
 *
 * Functions for using the i8254 timers
 */

/**
 * @brief Subscribes and enables Timer 0 interrupts
 *
 * @return Returns bit order in interrupt mask; negative value on failure
 */
int timer_subscribe_int(void );

/**
 * @brief Unsubscribes Timer 0 interrupts
 *
 * @return Return 0 upon success and non-zero otherwise
 */
int timer_unsubscribe_int();

/**
 * @brief Timer 0 interrupt handler
 *
 * Increments counter
 */
void timer_int_handler();

/**
 * @brief Waits for time in seconds
 *
 * Subscribes Timer 0 interrupts and
 * waits for time seconds.
 * Then unsubscribes Timer 0 interrupts.
 *
 * @param time Time in seconds to wait
 * @return Return 0 upon success and non-zero otherwise
 */
int wait(unsigned long time);

#endif /* __TIMER_H */
