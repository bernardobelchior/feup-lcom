#include "menu.h"
#include <stdlib.h>

menu* create_menu(const char* font_name){
	menu* m = (menu*) malloc(sizeof(menu));
	m->buttons_size = 0;
	m->buttons = 0;
	m->selected_button = -1;
	m->f = font_init(font_name);
	return m;
}

void menu_add_button(menu* m, button* b){
	m->buttons_size++;
	m->buttons = (button**) realloc(m->buttons, m->buttons_size*sizeof(button*));
	m->buttons[m->buttons_size-1] = b;
}

void menu_delete_button(menu* m, unsigned char index){
	free(m->buttons[index]);
	unsigned int i;
	for(i = index; i < m->buttons_size-1; i++ ){
		m->buttons[i] == m->buttons[i+1];
	}
	m->buttons_size--;
	m->buttons = (button**) realloc(m->buttons, m->buttons_size*sizeof(button*));
}

void menu_draw(menu* m){
	unsigned char i;
	for(i = 0; i < m->buttons_size; i++){
		button_draw(m->buttons[i], m->f);
	}
	if(m->selected_button != -1){
		button* selected = m->buttons[m->selected_button];
		vg_draw_frame(selected->x - 5, selected->y - 5, selected->width + 10, selected->height + 10, selected->color);
	}
}

unsigned char click_button(menu* m, short x, short y){
	unsigned char i;
	for(i = 0; i < m->buttons_size; i++){
		if(collides_with_button(m->buttons[i], x, y)){
			m->buttons[i]->function();
			return 1;
		}
	}
	return 0;
}

unsigned char previous_button(menu* m){
	if(m->selected_button > 0){
		m->selected_button--;
		return 0;
	}

	return 1;
}

unsigned char next_button(menu* m){
	if(m->selected_button < m->buttons_size - 1){
		m->selected_button++;
		return 0;
	}

	return 1;
}

void cancel_button(menu* m){
	m->selected_button = -1;
}

unsigned char press_selected_button(menu* m){
	if(m->selected_button == -1)
		return 1;

	(*(m->buttons[m->selected_button]->function))();
}

void delete_menu(menu* m){
	unsigned int i;
	for(i = 0; i < m->buttons_size; i++){
		button_delete(m->buttons[i]);
	}
	free(m->buttons);
	font_delete(m->f);
	free(m);
}
