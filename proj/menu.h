#ifndef MENU_H
#define MENU_H

#include "button.h"
#include "video_gr.h"

/** @name Menu Information Struct*/
/**@{
 *
 * Struct that stores info regarding a menu and its buttons
 */
typedef struct{
	button* (*buttons);
	unsigned char buttons_size;
	char selected_button;
} menu;
/** @} end of Menu Information Struct */

/**
 * @brief Initializes menu struct
 *
 * @return Returns pointer to initialized menu
 */
menu* create_menu();

/**
 * @brief Adds button to menu
 *
 * @param m Menu in which to add the button
 * @param b Button to be added
 */
void menu_add_button(menu* m, button* b);

/**
 * @brief Deletes button from menu and updates the array. Frees the deleted button.
 *
 * @param m Menu in which to delete the button
 * @param index Index of button to be destroyed
 */
void menu_delete_button(menu* m, unsigned char index);

/**
 * @brief Draws every button in the menu
 *
 * @param m Menu to draw
 */
void menu_draw(menu* m);

/**
 * @brief Checks if a button contained in menu is clicked and calls its function.
 *
 * @param m Menu in which to check
 * @param x Mouse position in the x axis
 * @param y Mouse position in the y axis
 *
 * @return Returns 1 if a button was clicked. Returns 0 otherwise.
 */
unsigned char click_button(menu* m, unsigned short x, unsigned short y);

/**
 * @brief Select previous button on screen
 *
 * @param m Menu info
 */
unsigned char previous_button(menu* m);

/**
 * @brief Select next button on screen
 *
 * @param m Menu info
 */
unsigned char next_button(menu* m);

/**
 * @brief Resets button selection
 *
 * @param m Menu info
 */
void cancel_button(menu* m);

/**
 * @brief Pressed the selected button by calling its function
 *
 * @param m Menu info
 */
unsigned char press_selected_button(menu* m);

/**
 * @brief Deletes and frees menu and its buttons.
 *
 * @param m Menu to be deleted
 */
void delete_menu(menu* m);

#endif
