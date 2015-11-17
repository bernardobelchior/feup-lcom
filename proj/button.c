#include "button.h"

button* create_button(unsigned short x, unsigned short y, unsigned short width, unsigned short height, void (*function)(), unsigned char color){
	button* b = (button*) malloc(sizeof(button));
	b->x = x;
	b->y = y;
	b->width = width;
	b->height = height;
	b->function = function;
	b->color = color;
	return b;
}

unsigned char collides_with_button(button* b, unsigned short x, unsigned short y){
	if(x > b->x && x < (b->x + b->width) && y > b->y && y < (b->y + b->height))
		return 1;
	else
		return 0;
}
