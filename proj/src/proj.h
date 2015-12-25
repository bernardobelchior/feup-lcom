#ifndef PROJ_H
#define PROJ_H

#define DEBUG

#include <minix/drivers.h>
#include <stdlib.h>
#include <string.h>

#include "font.h"
#include "video_gr.h"
#include "mouse.h"
#include "vbe.h"
#include "keyboard.h"
#include "i8042.h"
#include "menu.h"

font* space_invaders_font;
enum singleplayer_controller { keyboard = 0, mouse = 1 } controller;

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
