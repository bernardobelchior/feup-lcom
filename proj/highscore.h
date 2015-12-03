#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <stdio.h>
#include "menu.h"

#define MAX_NUMBER_OF_SCORES 10

typedef struct{
	char* name;
	unsigned int points;
} score;

static char highscore_path[] = "/home/lcom/lcom1516-t6g12/proj/highscore.txt";
static score** highscores;
static unsigned char highscore_size;
menu* highscore_menu;

int highscore_init();

score* highscore_read(FILE* file);

int highscore_add(char* name, unsigned int points);

int highscore_write(FILE* file, score* sc);

void highscore_tick();

int highscore_destruct();



#endif
