#ifndef EVENTS_H
#define EVENTS_H

#include "state.h"
#include "singleplayer.h"
#include "options.h"
#include "start_menu.h"

//Event Handlers

/**
 * @brief Keyboard event handler
 *
 * @param key Key read from the keyboard
 */
void kb_event_handler(unsigned short key);

/**
 * @brief Event thrown when a full mouse packet is read
 *
 * @param packet Packet read
 */
void mouse_event_handler(unsigned char packet[3]);

//Keyboard Events

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

//Mouse Events

/**
 * @brief Event thrown on middle mouse button released
 */
void mmb_released();

/**
 * @brief Event thrown on middle mouse button pressed
 */
void mmb_pressed();

/**
 * @brief Event thrown on right mouse button released
 */
void rmb_released();

/**
 * @brief Event thrown on right mouse button pressed
 */
void rmb_pressed();

/**
 * @brief Event thrown on left mouse button released
 */
void lmb_released();

/**
 * @brief Event thrown on left mouse button pressed
 */
void lmb_pressed();

//Timer Events

/**
 * @brief Event thrown on every tick defined in timer.h. Updates screen.
 */
void tick();

#endif
