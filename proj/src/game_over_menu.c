#include "game_over_menu.h"

void game_over_menu_init(unsigned int points){
	game_over_menu = create_menu("spaceinvader_font_transparent.bmp");
	state = game_over;

	//Accept and Clear buttons.
	menu_add_button(game_over_menu, create_button(312, 600, 100, 100, ALIGN_CENTER, &game_over_accept_button, "Accept", rgb(0xFFFFFF), ALIGN_CENTER));
	menu_add_button(game_over_menu, create_button(712, 600, 100, 100, ALIGN_CENTER, &game_over_clear_button, "Clear", rgb(0xFFFFFF), ALIGN_CENTER));

	//Next and previous buttons.
	menu_add_button(game_over_menu, create_button(412, 150, 75, 45, ALIGN_CENTER, &game_over_first_letter_prev, "", rgb(0xFFFFFF), ALIGN_CENTER));
	menu_add_button(game_over_menu, create_button(412, 250, 75, 45, ALIGN_CENTER, &game_over_first_letter_next, "", rgb(0xFFFFFF), ALIGN_CENTER));
	menu_add_button(game_over_menu, create_button(512, 150, 75, 45, ALIGN_CENTER, &game_over_second_letter_prev, "", rgb(0xFFFFFF), ALIGN_CENTER));
	menu_add_button(game_over_menu, create_button(512, 250, 75, 45, ALIGN_CENTER, &game_over_second_letter_next, "", rgb(0xFFFFFF), ALIGN_CENTER));
	menu_add_button(game_over_menu, create_button(612, 150, 75, 45, ALIGN_CENTER, &game_over_third_letter_prev, "", rgb(0xFFFFFF), ALIGN_CENTER));
	menu_add_button(game_over_menu, create_button(612, 250, 75, 45, ALIGN_CENTER, &game_over_third_letter_next, "", rgb(0xFFFFFF), ALIGN_CENTER));

	game_over_info.letters[0] = 'A';
	game_over_info.letters[1] = 'A';
	game_over_info.letters[2] = 'A';
	game_over_info.letters[3] = '\0';
	game_over_info.points = points;
}

void game_over_menu_tick(){
	font_draw_string(space_invaders_font, 512, 50, "Game over :(", ALIGN_CENTER);
	font_draw_char(space_invaders_font, 412, 200, game_over_info.letters[0], ALIGN_CENTER);
	font_draw_char(space_invaders_font, 512, 200, game_over_info.letters[1], ALIGN_CENTER);
	font_draw_char(space_invaders_font, 612, 200, game_over_info.letters[2], ALIGN_CENTER);
	menu_draw(game_over_menu);
}

void game_over_accept_button(){
	highscore_add(game_over_info.letters, get_todays_date(), game_over_info.points);
	game_over_menu_destruct();
}

void game_over_clear_button(){
	game_over_info.letters[0] = 'A';
	game_over_info.letters[1] = 'A';
	game_over_info.letters[2] = 'A';
}

void game_over_first_letter_prev(){
	if(game_over_info.letters[0] == 'A')
		game_over_info.letters[0] = 'Z';
	else
		game_over_info.letters[0]--;
}

void game_over_first_letter_next(){
	if(game_over_info.letters[0] == 'Z')
		game_over_info.letters[0] = 'A';
	else
		game_over_info.letters[0]++;
}

void game_over_second_letter_prev(){
	if(game_over_info.letters[1] == 'A')
		game_over_info.letters[1] = 'Z';
	else
		game_over_info.letters[1]--;
}

void game_over_second_letter_next(){
	if(game_over_info.letters[1] == 'Z')
		game_over_info.letters[1] = 'A';
	else
		game_over_info.letters[1]++;
}

void game_over_third_letter_prev(){
	if(game_over_info.letters[2] == 'A')
		game_over_info.letters[2] = 'Z';
	else
		game_over_info.letters[2]--;
}

void game_over_third_letter_next(){
	if(game_over_info.letters[2] == 'Z')
		game_over_info.letters[2] = 'A';
	else
		game_over_info.letters[2]++;
}

void game_over_menu_destruct(){
	delete_menu(game_over_menu);
	free(game_over_info.letters);
	state = singleplayer;
}
