#ifndef STATE_H
#define STATE_H

#include "game_over_menu.h"

/** @defgroup state state
 * @{
 * state
 */

enum game_state { main_menu, singleplayer, game_over, multiplayer, highscore, options} state;

/**
 * @brief initializes a state
 */
void init_state();

/**
 * @brief changes to a new state, deleting the previous one
 */
void change_state(enum game_state new_state);

/**
 * @brief deletes all the information and structures needed in a state
 */
void delete_state();

#endif
