#ifndef ANIMATION_H
#define ANIMATION_H

#include "bitmap.h"
#include "proj.h"

typedef struct sprite sprite;

struct sprite{
	bitmap* bmp;
	sprite* next;
};

typedef struct{
	sprite* head;
	sprite* current;
} animation; //circular list


animation* animation_init();

void animation_add(animation* a, const char* filename);

void animation_next(animation* a);

void animation_destruct(animation* a);

#endif
