#include "game_over_menu.h"

void game_over_menu_init(){
	game_over_menu = create_menu("spaceinvader_font_transparent.bmp");
	up = bitmap_load("up_arrow.bmp");
	down = bitmap_load("down_arrow.bmp");

	//Accept and Clear buttons.
	menu_add_button(game_over_menu, create_button(312, 600, 250, 100, ALIGN_CENTER, &game_over_accept_button, "Accept", rgb(0xFFFFFF), ALIGN_CENTER));
	menu_add_button(game_over_menu, create_button(712, 600, 250, 100, ALIGN_CENTER, &game_over_clear_button, "Clear", rgb(0xFFFFFF), ALIGN_CENTER));

	//Next and previous buttons.
	button* first_letter_prev = create_button(412, 260, 48, 29, ALIGN_CENTER, &game_over_first_letter_prev, NULL, rgb(0xFFFFFF), ALIGN_CENTER);
	button_set_background(first_letter_prev, up);
	menu_add_button(game_over_menu, first_letter_prev);

	button* first_letter_next = create_button(412, 355, 48, 29, ALIGN_CENTER, &game_over_first_letter_next, NULL, rgb(0xFFFFFF), ALIGN_CENTER);
	button_set_background(first_letter_next, down);
	menu_add_button(game_over_menu, first_letter_next);

	button* second_letter_prev = create_button(512, 260, 48, 29, ALIGN_CENTER, &game_over_second_letter_prev, NULL, rgb(0xFFFFFF), ALIGN_CENTER);
	button_set_background(second_letter_prev, up);
	menu_add_button(game_over_menu, second_letter_prev);

	button* second_letter_next = create_button(512, 355, 48, 29, ALIGN_CENTER, &game_over_second_letter_next, NULL, rgb(0xFFFFFF), ALIGN_CENTER);
	button_set_background(second_letter_next, down);
	menu_add_button(game_over_menu, second_letter_next);

	button* third_letter_prev = create_button(612, 260, 48, 29, ALIGN_CENTER, &game_over_third_letter_prev, NULL, rgb(0xFFFFFF), ALIGN_CENTER);
	button_set_background(third_letter_prev, up);
	menu_add_button(game_over_menu, third_letter_prev);

	button* third_letter_next = create_button(612, 355, 48, 29, ALIGN_CENTER, &game_over_third_letter_next, NULL, rgb(0xFFFFFF), ALIGN_CENTER);
	button_set_background(third_letter_next, down);
	menu_add_button(game_over_menu, third_letter_next);

	new_score.letters[0] = 'A';
	new_score.letters[1] = 'A';
	new_score.letters[2] = 'A';
	new_score.letters[3] = '\0';
}

void game_over_menu_tick(){
	font_draw_string(space_invaders_font, 512, 50, "Game over :(", ALIGN_CENTER);
	font_draw_char(space_invaders_font, 412, 300, new_score.letters[0], ALIGN_CENTER);
	font_draw_char(space_invaders_font, 512, 300, new_score.letters[1], ALIGN_CENTER);
	font_draw_char(space_invaders_font, 612, 300, new_score.letters[2], ALIGN_CENTER);
	font_draw_string(space_invaders_font, 562, 450, "Score: ", ALIGN_RIGHT);
	font_draw_int(space_invaders_font, 562, 450, new_score.points, ALIGN_LEFT);
	menu_draw(game_over_menu);
}

void game_over_accept_button(){
	highscore_add(new_score.letters, get_todays_date(), new_score.points);
	change_state(main_menu);
}

void game_over_clear_button(){
	new_score.letters[0] = 'A';
	new_score.letters[1] = 'A';
	new_score.letters[2] = 'A';
}

void game_over_first_letter_prev(){
	if(new_score.letters[0] == 'A')
		new_score.letters[0] = 'Z';
	else
		new_score.letters[0]--;
}

void game_over_first_letter_next(){
	if(new_score.letters[0] == 'Z')
		new_score.letters[0] = 'A';
	else
		new_score.letters[0]++;
}

void game_over_second_letter_prev(){
	if(new_score.letters[1] == 'A')
		new_score.letters[1] = 'Z';
	else
		new_score.letters[1]--;
}

void game_over_second_letter_next(){
	if(new_score.letters[1] == 'Z')
		new_score.letters[1] = 'A';
	else
		new_score.letters[1]++;
}

void game_over_third_letter_prev(){
	if(new_score.letters[2] == 'A')
		new_score.letters[2] = 'Z';
	else
		new_score.letters[2]--;
}

void game_over_third_letter_next(){
	if(new_score.letters[2] == 'Z')
		new_score.letters[2] = 'A';
	else
		new_score.letters[2]++;
}

void game_over_menu_destruct(){
	delete_menu(game_over_menu);
}
