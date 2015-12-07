#ifndef FONT_H
#define FONT_H

#include "bitmap.h"
#include <stdio.h>

//change bitmap_draw to have 3 args: bitmap_data, width and height
//16 pixels width
//44 pixels height

#define LETTER_HEIGHT 44
#define LETTER_WIDTH 16

static char font_path[] = "font/";

typedef struct{
	unsigned char lower_limit, higher_limit, letters_per_line;
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
* @param x Position on the x axis to print the string
* @param y Position on the y axis to print the string
* @param str String to print
*/

void font_draw_string(font* f, unsigned short x, unsigned short y, const char* str);

/**
 * @brief Delete font
 *
 * @param f Font to be deleted
 */

void font_delete(font* f);

#endif
