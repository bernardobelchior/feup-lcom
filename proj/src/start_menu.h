#ifndef START_MENU_H
#define START_MENU_H

#include "menu.h"

/** @defgroup start_menu start_menu
 * @{
 * start menu
 */

extern font* space_invaders_font;
menu* start_menu;
bitmap* title;

/**
 * @brief initializes the start menu
 */
void start_menu_init();

/**
 * @brief draws the main menu on the screen
 */
void start_menu_draw();

/**
 * @brief goes to the singleplayer
 */
void start_menu_singleplayer_on_click();

/**
 * @brief goes to the multiplayer
 */
void start_menu_multiplayer_on_click();

/**
 * @brief goes to the highscore table
 */
void start_menu_highscore_on_click();

/**
 *@brief goes to the options menu
 */
void start_menu_options_on_click();


/**
 * @brief exits the game
 */
void start_menu_exit_on_click();


/**
 * @brief deletes the start menu
 */
void start_menu_destruct();

#endif
