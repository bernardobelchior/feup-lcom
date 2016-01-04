#ifndef ANIMATION_H
#define ANIMATION_H

#include "proj.h"

typedef struct sprite sprite;

struct sprite{
	bitmap* bmp;
	unsigned char delete_on_destruct;
	sprite* next;
};

typedef struct{
	sprite* head;
	sprite* current;
} animation; //circular list

/**
 * @brief Initializes animation
 *
 * @return Returns animation
 */
animation* animation_init();

/**
 * @brief Adds a sprite to the animation
 *
 * @param a Animation
 * @param filename Name of the image file
 */
void animation_add_by_filename(animation* a, const char* filename);

/**
 * @brief Adds a sprite to the animation
 *
 * @param a Animation
 * @param bmp Bitmap
 */
void animation_add_by_bmp(animation* a, bitmap* bmp);

/**
 * @brief Goes to next sprite
 *
 * @param a Animation
 */
void animation_next(animation* a);

/**
 * @brief Destructs animation
 *
 * @param a Animation
 */
void animation_destruct(animation* a);

#endif
