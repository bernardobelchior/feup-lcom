#include "start_menu.h"
#include "state.h"
#include "video_gr.h"
#include "font.h"

void start_menu_init(){
	start_menu = create_menu("spaceinvader_font_transparent.bmp");

	button* singleplayer = create_button(512, 250, 500, 90, ALIGN_CENTER, &start_menu_singleplayer_on_click, "Singleplayer", rgb(0xFFFFFF), ALIGN_CENTER);
	menu_add_button(start_menu, singleplayer);
	button* multiplayer = create_button(512, 350, 500, 90, ALIGN_CENTER, &start_menu_multiplayer_on_click, "Multiplayer", rgb(0xFFFFFF), ALIGN_CENTER);
	menu_add_button(start_menu, multiplayer);
	button* highscore = create_button(512, 450, 500, 90, ALIGN_CENTER, &start_menu_highscore_on_click, "Highscores", rgb(0xFFFFFF), ALIGN_CENTER);
	menu_add_button(start_menu, highscore);
	button* options = create_button(512, 550, 500, 90, ALIGN_CENTER, &start_menu_options_on_click, "Options", rgb(0xFFFFFF), ALIGN_CENTER);
	menu_add_button(start_menu, options);
	button* exit = create_button(512, 650, 500, 90, ALIGN_CENTER, &start_menu_exit_on_click, "Exit", rgb(0xFFFFFF), ALIGN_CENTER);
	menu_add_button(start_menu, exit);

	title = bitmap_load("title.bmp");
}

void start_menu_draw(){
	bitmap_draw(title, get_h_res()/2, 25, ALIGN_CENTER);
	menu_draw(start_menu);
	mouse_draw();
}

void start_menu_singleplayer_on_click(){
	change_state(singleplayer);
}

void start_menu_multiplayer_on_click(){
	change_state(multiplayer);
}

void start_menu_highscore_on_click(){
	change_state(highscore);
}

void start_menu_options_on_click(){
	change_state(options);
}

void start_menu_exit_on_click(){
	leave();
}

void start_menu_destruct(){
	delete_menu(start_menu);
	bitmap_delete(title);
}
