#ifndef GAME_OVER_MENU
#define GAME_OVER_MENU

#include "highscore.h"
#include "menu.h"
#include "font.h"
#include "state.h"

struct {
	char letters[4];
	unsigned int points;
} game_over_info;

menu* game_over_menu;

extern enum game_state state;

extern font* space_invaders_font;

void game_over_menu_init(unsigned int points);

void game_over_menu_tick();

void game_over_accept_button();

void game_over_clear_button();

void game_over_first_letter_prev();

void game_over_first_letter_next();

void game_over_second_letter_prev();

void game_over_second_letter_next();

void game_over_third_letter_prev();

void game_over_third_letter_next();

void game_over_menu_destruct();

#endif
