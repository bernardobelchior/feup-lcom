#ifndef EVENTS_H
#define EVENTS_H

/**
 * @brief Initializes mouse struct
 */
void mouse_init();

/**
 * @brief Keyboard event handler
 *
 * @param key Key read from the keyboard
 */
void kb_event_handler(unsigned long key);

/**
 * @brief Event thrown when a full mouse packet is read
 *
 * @param packet Packet read
 */
void mouse_event_handler(unsigned char packet[3]);

/**
 * @brief Event thrown on key pressed
 *
 * @param key Key pressed make code
 */
void key_pressed(unsigned long key);

/**
 * @brief Event thrown on key released
 *
 * @param key Key pressed break code
 */
void key_released(unsigned long key);

#endif
