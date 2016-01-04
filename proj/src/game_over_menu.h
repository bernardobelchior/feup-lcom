#ifndef GAME_OVER_MENU
#define GAME_OVER_MENU

#include "highscore.h"
#include "menu.h"
#include "font.h"
#include "state.h"

/** @defgroup Game_over_menu Game_over_menu
 * @{
 * Game over menu
 */

typedef struct {
	char letters[4];
	unsigned int points;
} game_over_info;

game_over_info new_score;
menu* game_over_menu;
extern enum game_state state;
extern font* space_invaders_font;
bitmap *up, *down;

/**
 * @brief initializes the information referring to the game over menu
 */
void game_over_menu_init();

/**
 * @brief keeps and updates (if necessary) the information referring to the game over menu on the screen
 */
void game_over_menu_tick();

/**
 * @brief button that when pressed changes the state back to the main menu
 */
void game_over_accept_button();

/**
 * @brief button that when pressed clears the name to be inserted on the highscores
 */
void game_over_clear_button();

/**
 * @brief changes the first letter to the previous in alphabetic order
 */
void game_over_first_letter_prev();

/**
 * @brief changes the first letter to the next in alphabetic order
 */
void game_over_first_letter_next();

/**
 * @brief changes the second letter to the previous in alphabetic order
 */
void game_over_second_letter_prev();

/**
 * @brief changes the first letter to the next in alphabetic order
 */
void game_over_second_letter_next();

/**
 * @brief changes the first letter to the previous in alphabetic order
 */
void game_over_third_letter_prev();

/**
 * @brief changes the first letter to the next in alphabetic order
 */
void game_over_third_letter_next();

/**
 * @brief deletes the information referring to the game over menu
 */
void game_over_menu_destruct();

#endif
