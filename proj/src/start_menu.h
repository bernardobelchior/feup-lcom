#ifndef START_MENU_H
#define START_MENU_H

#include "menu.h"

extern font* space_invaders_font;
menu* start_menu;

void start_menu_init();

void start_menu_draw();

void start_menu_singleplayer_on_click();

void start_menu_multiplayer_on_click();

void start_menu_highscore_on_click();

void start_menu_options_on_click();

void start_menu_exit_on_click();

void start_menu_destruct();

#endif
