#ifndef FONT_H
#define FONT_H

#include "bitmap.h"

/** @defgroup Font Font
 * @{
 * Font drawing and struct
 */

#define LETTER_HEIGHT 44
#define LETTER_WIDTH 32
#define LETTER_SPACEMENT 3

static char font_path[] = "";

typedef struct{
	unsigned char lower_limit, higher_limit, letters_per_line;
	unsigned short letter_width, letter_height;
	bitmap* letters;
} font; 

/**
* @brief Initializes font stored in filename, in the font_path directory.
*
* @return Returns pointer to font
*/
font* font_init(const char* filename);

/**
* @brief Draws string on x,y position
*
* @param f Font to draw string with
* @param x Position on the x axis to print the string
* @param y Position on the y axis to print the string
* @param str String to print
* @param alignment String alignement
*/
void font_draw_string(font* f, short x, short y, const char* str, Alignment alignment);

/**
 * @brief Draws an integer on x,y position
 *
 * @param x Position on the x axis to print the integer
 * @param y Position on the y axis to print the integer
 * @param number Integer to print
 * @param base Base in which the integer is given
 * @param alignment Integer alignment
 */
void font_draw_int(font* f, short x, short y, int number, Alignment alignment);

/**
 * @brief Changes the color in the font
 *
 * @param f Font to recolor
 * @param initial_color Color to replace
 * @param final_color Color to replace with
 */
void font_recolor(font* f, unsigned short initial_color, unsigned short final_color);

/**
 * @brief Draws char on specified position
 *
 * @param f Font with which to draw
 * @param x Position in the x axis
 * @param y Position in the y axis
 * @param c Character to draw
 * @param alignment Character alignment
 */
void font_draw_char(font *f, short x, short y, char c, Alignment alignment);

/**
 * @brief Delete font
 *
 * @param f Font to be deleted
 */
void font_delete(font* f);

#endif
