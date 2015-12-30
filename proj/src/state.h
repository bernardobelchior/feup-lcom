#ifndef STATE_H
#define STATE_H

#include "game_over_menu.h"

enum game_state { main_menu, singleplayer, game_over, multiplayer, highscore, options} state;

void init_state();

void change_state(enum game_state new_state);

void delete_state();

#endif
