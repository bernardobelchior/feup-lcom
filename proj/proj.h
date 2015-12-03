#ifndef PROJ_H
#define PROJ_H

#include "mouse.h"
#include "menu.h"

enum game_state { main_menu, singleplayer, multiplayer, highscore, options };
enum singleplayer_controller { keyboard = 0, mouse = 1 };

enum singleplayer_controller controller;
enum game_state state;
menu* start_menu;

/**
 * @brief Main function
 *
 * @param argc Argument count
 * @param argv Array of arguments
 *
 * @return Returns 0 on success and non-zero otherwise.
 */
int main(int argc, char **argv);

/**
 * @brief Initializes mouse, interrupts, creates main menu and handles interrupts.
 *
 * @return Returns 0 on success and non-zero otherwise.
 */
int start();

/**
 * @brief Initializes start menu.
 */
void start_menu_init();

/**
 * @brief Destructs start menu.
 */
void start_menu_destruct();

/**
 * @brief Unsubscribes the used interrupts. Deletes menus and leaves program.
 */
void leave();

#endif
