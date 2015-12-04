#ifndef OPTIONS_H
#define OPTIONS_H

#include "menu.h"

menu* options_menu;
static char options_path[] = "/home/lcom/lcom1516-t6g12/proj/options.cfg";

void options_init();

void options_tick();

void options_save();

void options_load();

void options_accept_on_click();

void options_cancel_on_click();

void options_destruct();

#endif
