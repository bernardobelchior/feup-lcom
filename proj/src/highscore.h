#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include "proj.h"
#include "state.h"
#include "rtc.h"

#define MAX_NUMBER_OF_SCORES 10

typedef struct{
	char* name;
	Date* date;
	unsigned int points;
} score;

static char highscore_path[] = "/home/proj/cfg/highscore.txt";
static score** highscores;
static unsigned char highscore_size;
menu* highscore_menu;
extern font* space_invaders_font;

void highscore_init();

score* highscore_read(FILE* file);

int highscore_add(char* name, Date* date, unsigned int points);

int highscore_write(FILE* file, score* sc);

int is_on_highscores(unsigned int points);

void highscore_tick();

void highscore_back_on_click();

void highscore_destruct();



#endif
