#ifndef OPTIONS_H
#define OPTIONS_H

#include "menu.h"

menu* options_menu;
static char options_path[] = "/home/proj/cfg/options.cfg";
extern font* space_invaders_font;
bitmap *next, *prev;

/**
 * @brief Initializes options
 */
void options_init();

/**
 * @brief Handles a tick on options menu
 */
void options_tick();

/**
 * @brief Saves the current configuration to a file
 */
void options_save();

/**
 * @brief Loads a stored configuration from a file
 */
void options_load();

/**
 * @brief Handles what happens when the "Accept" button is clicked
 */
void options_accept_on_click();

/**
 * @brief Handles what happens when the "Cancel" button is clicked
 */
void options_cancel_on_click();

/**
 * @brief Handles what happens when the next controller button is clicked
 */
void options_next_ctrl_on_click();

/**
 * @brief Handles what happens when the previous controller button is clicked
 */
void options_prev_ctrl_on_click();

/**
 * @brief Destructs options
 */
void options_destruct();

#endif
