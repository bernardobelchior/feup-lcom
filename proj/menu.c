#include "menu.h"

menu* create_menu(){
	menu* m = (menu*) malloc(sizeof(menu));
	m->buttons_size = 0;
	m->buttons = 0;
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

unsigned char click_button(menu* m, unsigned short x, unsigned short y){
	unsigned char i;
	for(i = 0; i < m->buttons_size; i++){
		if(collides_with_button(m->buttons[i], x, y)){
			if(m->buttons[i]->function != 0)
				(*(m->buttons[i]->function))();
			return 1;
		}
	}
	return 0;
}

void delete_menu(menu* m){
	unsigned int i;
	for(i = 0; i < m->buttons_size; i++){
		free(m->buttons[i]);
	}
	free(m->buttons);
}
