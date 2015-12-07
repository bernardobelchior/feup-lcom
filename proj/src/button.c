#include "button.h"
#include "video_gr.h"

button* create_button(short x, short y, unsigned short width, unsigned short height, void (*function)(), const char* title, unsigned short color){
	button* b = (button*) malloc(sizeof(button));
	b->x = x;
	b->y = y;
	b->width = width;
	b->height = height;
	b->function = function;
	b->color = color;
	b->title = (char*) malloc(strlen(title)*sizeof(char));
	strcpy(b->title, title);
	return b;
}

void button_draw(button* b, font* f){
	vg_draw_frame(b->x, b->y, b->width, b->height, b->color);
	if(f != NULL)
		font_draw_string(f, b->x+5, b->y+5, b->title);
}

char collides_with_button(button* b, short x, short y){
	if(x > b->x && x < (b->x + b->width) && y > b->y && y < (b->y + b->height))
		return 1;
	else
		return 0;
}

void button_delete(button* b){
	free(b->title);
	free(b);
}
