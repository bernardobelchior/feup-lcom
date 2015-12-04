#ifndef BUTTON_H
#define BUTTON_H

#include "state.h"

/** @name Button Information Struct*/
/**@{
 *
 * Struct that stores info regarding a button
 */
typedef struct { //TODO still have to add text or image
	unsigned short x, y, width, height;
	void (*function)();
	unsigned char color;
} button;
/** @} end of Button Information Struct */

/**
 * @brief Creates and initializes a button
 *
 * @param x Upper left corner position of the button, in the x axis
 * @param y Upper left corner position of the button, in the y axis
 * @param width Button width
 * @param height Button height
 * @param function Function to call when the button is clicked
 * @param color Color with which to color the button
 *
 * @return Returns the button created
 */
button* create_button(unsigned short x, unsigned short y, unsigned short width, unsigned short height, void (*function)(), unsigned char color);

/**
 * @brief Draws button
 *
 * @param b Button to be drawn
 */
void button_draw(button* b);

/**
 * @brief Checks if the position (x,y) is inside the button
 *
 * @param b Button to check
 * @param x Position in relation to the x axis
 * @param y Position in relation to the y axis
 *
 * @return Returns 1 if the check is true. Returns 0 otherwise.
 */
char collides_with_button(button* b, unsigned short x, unsigned short y);

#endif
