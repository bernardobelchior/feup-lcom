#include "options.h"
#include "proj.h"
#include "button.h"
#include "state.h"
#include "video_gr.h"
#include <stdio.h>

extern enum singleplayer_controller controller;
enum singleplayer_controller temp;

void options_init(){
	options_menu = (menu*) malloc(sizeof(menu));
	options_menu = create_menu("spaceinvader_font_transparent.bmp");
	menu_add_button(options_menu, create_button(200, 650, 200, 100, &options_accept_on_click, "Accept", rgb(0xFFFFFF)));
	menu_add_button(options_menu, create_button(600, 650, 200, 100, &options_cancel_on_click, "Cancel", rgb(0xFFFFFF)));
	temp = controller;
}

void options_tick(){
	menu_draw(options_menu);
	vg_draw_frame(100, 150, 800, 450, rgb(0xFFFFFF));

	//Vertical lines
	vg_draw_line(400, 150, 400, 600, rgb(0xFFFFFF));
}

void options_save(){
	FILE* file = fopen(options_path, "w");

	fprintf(file, "CONTROLLER = %u", controller);

	fclose(file);
}

void options_load(){
	FILE* file = fopen(options_path, "r");
	unsigned char control = 0;

	if(feof(file))
		control = 0;

	fscanf(file, "CONTROLLER = %u", &control);

	fclose(file);

	if(control == 1)
		controller = mouse;
	else
		controller = keyboard;
}

void options_accept_on_click(){
	controller = temp;
	change_state(main_menu);
}

void options_cancel_on_click(){
	change_state(main_menu);
}

void options_destruct(){
	delete_menu(options_menu);
	start_menu_init();
}
