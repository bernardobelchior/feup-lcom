#include "start_menu.h"
#include "state.h"
#include "video_gr.h"

void start_menu_init(){
	start_menu = create_menu("spaceinvader_font_transparent.bmp");

	button* singleplayer = create_button(512, 200, 200, 90, ALIGN_CENTER, &start_menu_singleplayer_on_click, "Singleplayer", rgb(0xFFFFFF), ALIGN_CENTER);
	menu_add_button(start_menu, singleplayer);
	button* multiplayer = create_button(512, 300, 200, 90, ALIGN_CENTER, &start_menu_multiplayer_on_click, "Multiplayer", rgb(0xFFFFFF), ALIGN_CENTER);
	menu_add_button(start_menu, multiplayer);
	button* highscore = create_button(512, 400, 200, 90, ALIGN_CENTER, &start_menu_highscore_on_click, "Highscores", rgb(0xFFFFFF), ALIGN_CENTER);
	menu_add_button(start_menu, highscore);
	button* options = create_button(512, 500, 200, 90, ALIGN_CENTER, &start_menu_options_on_click, "Options", rgb(0xFFFFFF), ALIGN_CENTER);
	menu_add_button(start_menu, options);
	button* exit = create_button(512, 600, 200, 90, ALIGN_CENTER, &start_menu_exit_on_click, "Exit", rgb(0xFFFFFF), ALIGN_CENTER);
	menu_add_button(start_menu, exit);
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
}
