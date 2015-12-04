#include "button.h"
#include "video_gr.h"

button* create_button(unsigned short x, unsigned short y, unsigned short width, unsigned short height, void (*function)(), unsigned short color){
	button* b = (button*) malloc(sizeof(button));
	b->x = x;
	b->y = y;
	b->width = width;
	b->height = height;
	b->function = function;
	b->color = color;
	return b;
}

void button_draw(button* b){
	vg_draw_frame(b->x, b->y, b->width, b->height, b->color);
}

char collides_with_button(button* b, unsigned short x, unsigned short y){
	if(x > b->x && x < (b->x + b->width) && y > b->y && y < (b->y + b->height))
		return 1;
	else
		return 0;
}
