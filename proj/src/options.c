#include "options.h"
#include "proj.h"
#include "button.h"
#include "state.h"
#include "video_gr.h"
#include <stdio.h>

extern enum singleplayer_controller controller;
enum singleplayer_controller temp;

void options_init(){
	next = bitmap_load("right_arrow.bmp");
	prev = bitmap_load("left_arrow.bmp");

	options_menu = (menu*) malloc(sizeof(menu));
	options_menu = create_menu("spaceinvader_font_transparent.bmp");
	menu_add_button(options_menu, create_button(300, 650, 200, 100, ALIGN_CENTER, &options_accept_on_click, "Accept", rgb(0xFFFFFF), ALIGN_CENTER));
	menu_add_button(options_menu, create_button(700, 650, 200, 100, ALIGN_CENTER, &options_cancel_on_click, "Cancel", rgb(0xFFFFFF), ALIGN_CENTER));

	button* next_button = create_button(850, 175, 30, 50, ALIGN_CENTER, &options_next_ctrl_on_click, NULL, rgb(0xFFFFFF), ALIGN_CENTER);
	button_set_background(next_button, next);
	menu_add_button(options_menu, next_button);

	button* prev_button = create_button(450, 175, 30, 50, ALIGN_CENTER, &options_prev_ctrl_on_click, NULL, rgb(0xFFFFFF), ALIGN_CENTER);
	button_set_background(prev_button, prev);
	menu_add_button(options_menu, prev_button);

	temp = controller;
}

void options_tick(){
	//Title
	font_draw_string(space_invaders_font, get_h_res()/2, get_v_res()/20, "Options", ALIGN_CENTER);

	//Menu
	menu_draw(options_menu);

	//Frame
	vg_draw_frame(100, 150, 800, 450, rgb(0xFFFFFF));
	vg_draw_line(400, 150, 400, 600, rgb(0xFFFFFF));

	//Options
	font_draw_string(space_invaders_font, 375, 175, "Cont.:", ALIGN_RIGHT);

	//Display current configuration
	switch(temp){
	case keyboard:
		font_draw_string(space_invaders_font, 650, 175, "Keyboard", ALIGN_CENTER);
		break;
	case mouse:
		font_draw_string(space_invaders_font, 650, 175, "Mouse", ALIGN_CENTER);
	}
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

void options_next_ctrl_on_click(){
	switch(temp){
	case keyboard:
		temp = mouse;
		break;
	case mouse:
		temp = keyboard;
		break;
	}
}

void options_prev_ctrl_on_click(){
	options_next_ctrl_on_click();
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
	bitmap_delete(prev);
	bitmap_delete(next);
}
